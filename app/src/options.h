#ifndef OPTIONCLASS_H
#define OPTIONCLASS_H

#include <QObject>
#include <QQmlEngine>

/*!
 * \brief The Options class:
 * Options for the application, gets registerter to qml
 */
class Options : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Not creatable as it is an enum type")

public:
    enum AppMode { Gallery, Image, Video, Compare, Database, Empty };
    enum Menu { Path, Favorites, Trash, File };
    enum PathOptions { CurrentPath, FolderFile, DatabaseFile, FavoritesFolder, TrashFolder };
    enum Order { Name, Type, Recorded, Created, Modified };
    enum Direction { Up, Down };
    enum HeaderDirection { Disabled, Low, High };

    Q_ENUM(AppMode)
    Q_ENUM(Menu)
    Q_ENUM(PathOptions)
    Q_ENUM(Order)
    Q_ENUM(Direction)
    Q_ENUM(HeaderDirection)

private:
    explicit Options() {}
};

typedef Options::AppMode AppMode;
typedef Options::Menu Menu;
typedef Options::PathOptions PathOptions;
typedef Options::Order Order;
typedef Options::Direction Direction;
typedef Options::HeaderDirection HeaderDirection;

Q_DECLARE_METATYPE(AppMode)
Q_DECLARE_METATYPE(Menu)
Q_DECLARE_METATYPE(PathOptions)
Q_DECLARE_METATYPE(HeaderDirection)

#endif  // OPTIONCLASS_H
