#include "exivplugin.h"

ExivPlugin::ExivPlugin() {}

void ExivPlugin::exifInfo() {}

void ExivPlugin::exifPrint(const QString &path) { Q_UNUSED(path); }

QDateTime ExivPlugin::readDate(const QString &path) {
    Q_UNUSED(path);
    // Default time
    return QDateTime(QDate(1, 1, 1), QTime(0, 0));
}

QStringList ExivPlugin::readLabels(const QString &path) {
    Q_UNUSED(path);
    return QStringList();
}

void ExivPlugin::setLabels(const QString &path, const QStringList &labels) {
    Q_UNUSED(path);
    Q_UNUSED(labels);
}

void ExivPlugin::readMetadata(const QString &path) { Q_UNUSED(path); }

void ExivPlugin::writeMetadata(const QString &path) { Q_UNUSED(path); }
