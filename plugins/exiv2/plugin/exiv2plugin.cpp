#include "exiv2plugin.h"

#include <iostream>
#include <string>

Exiv2Plugin::Exiv2Plugin(QObject *parent) : QObject(parent) {
    m_name = "Exiv2 Plugin";
    m_icon = ":/exiv2/icon.png";
    m_info = "Image metadata library and tools";
    m_link = "https://github.com/Exiv2/exiv2";
    m_version = QString::fromStdString(Exiv2::version());

    // Force loading of the resources
    Q_INIT_RESOURCE(resource_exiv2);
}

void Exiv2Plugin::exifInfo() {
    std::vector<std::regex> keys;
    Exiv2::dumpLibraryInfo(std::cout, keys);

    std::cout << "EXV_PACKAGE_VERSION             " << EXV_PACKAGE_VERSION << std::endl
              << "Exiv2::version()                " << Exiv2::version() << std::endl
              << "strlen(Exiv2::version())        " << ::strlen(Exiv2::version()) << std::endl
              << "Exiv2::versionNumber()          " << Exiv2::versionNumber() << std::endl
              << "Exiv2::versionString()          " << Exiv2::versionString() << std::endl
              << "Exiv2::versionNumberHexString() " << Exiv2::versionNumberHexString() << std::endl;
}

void Exiv2Plugin::exifPrint(const QString &path) {
    // Exifprint example
    Exiv2::XmpParser::initialize();
    ::atexit(Exiv2::XmpParser::terminate);

    Exiv2::Image::UniquePtr image = readImage(path);
    Exiv2::ExifData &exifData = image->exifData();

    auto end = exifData.end();
    for (auto i = exifData.begin(); i != end; ++i) {
        const char *tn = i->typeName();
        std::cout << std::setw(44) << std::setfill(' ') << std::left << i->key() << " "
                  << "0x" << std::setw(4) << std::setfill('0') << std::right << std::hex << i->tag() << " " << std::setw(9)
                  << std::setfill(' ') << std::left << (tn ? tn : "Unknown") << " " << std::dec << std::setw(3)
                  << std::setfill(' ') << std::right << i->count() << "  " << std::dec << i->value() << "\n";
    }
}

QDateTime Exiv2Plugin::readDate(const QString &path) {
    // Default time
    QDateTime time(QDate(1, 1, 1), QTime(0, 0));

    Exiv2::Image::UniquePtr image = readImage(path);
    Exiv2::ExifData &exifData = image->exifData();
    std::string date = exifData["Exif.Photo.DateTimeDigitized"].toString();

    QStringList list = QString::fromStdString(date).split(' ');
    if (list.size() < 2) return time;

    time.setDate(QDate::fromString(list[0], "yyyy:MM:dd"));
    time.setTime(QTime::fromString(list[1], "hh:mm:ss"));
    return time;
}

QStringList Exiv2Plugin::readLabels(const QString &path) {
    Exiv2::Image::UniquePtr image = readImage(path);
    Exiv2::ExifData &exifData = image->exifData();
    std::string comment = exifData["Exif.Photo.UserComment"].toString();

    // Check for size or bug
    if (comment.length() > 4000 || !comment.compare("charset=\"Unicode\" ")) {
        qCritical() << "Error in metadata -> rewrite";
        exifData["Exif.Photo.UserComment"] = "charset=\"Unicode\"  ";  // Write whitespace to file
        image->writeMetadata();
        return QStringList();
    }

    QString data = QString::fromStdString(comment);
    data = data.replace("charset=Unicode ", "");  // Cut off: "charset=\"Unicode\" "
    QStringList labels = data.split("; ");        // Labels separated by ;
    labels.removeAll("");
    labels.removeAll(" ");
    return labels;
}

void Exiv2Plugin::setLabels(const QString &path, const QStringList &labels) {
    Exiv2::Image::UniquePtr image = readImage(path);
    Exiv2::ExifData &exifData = image->exifData();
    std::string data = labels.join("; ").toStdString();  // Labels separated by ;

    exifData["Exif.Photo.UserComment"] = "charset=\"Unicode\" " + data;
    image->writeMetadata();
}

void Exiv2Plugin::readMetadata(const QString &path) { m_metadata = readImage(path); }

void Exiv2Plugin::writeMetadata(const QString &path) {
    if (m_metadata.get() == 0) return;
    Exiv2::Image::UniquePtr image = readImage(path);
    image->setMetadata(*m_metadata);
    image->writeMetadata();
}

Exiv2::Image::UniquePtr Exiv2Plugin::readImage(const QString &path) {
    Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(path.toStdString());
    assert(image.get() != 0);
    image->readMetadata();
    return image;
}
