#include "listsort.h"


Order ListSort::actual_order = Order::Name;
Direction ListSort::actual_direction = Direction::Up;


void ListSort::order(FileList* fileList, Order order) // static
{
    if(actual_order == order)
        return;

    // Order changed
    actual_order = order;
    switch(actual_order)
    {
    case Order::Name:
    {
        QMap<int, QString*> map;
        for(int i = 0; i < fileList->size(); i++)
            map.insert(i, fileList->at(i)->name()); // Name

        sortList<QString>(fileList, map);
        qInfo() << "Sort list by name";
        break;
    }
    case Order::Type:
    {
        QMap<int, BaseFile::FileFormat*> map;
        for(int i = 0; i < fileList->size(); i++)
            map.insert(i, fileList->at(i)->fileformat()); // Type

        sortList<BaseFile::FileFormat>(fileList, map);
        qInfo() << "Sort list by type";
        break;
    }
    case Order::Recorded:
    {
        QMap<int, QDateTime*> map;
        for(int i = 0; i < fileList->size(); i++)
            map.insert(i, fileList->at(i)->recorded()); // Recorded

        sortList<QDateTime>(fileList, map);
        qInfo() << "Sort list by recorded";
        break;
    }
    case Order::Created:
    {
        QMap<int, QDateTime*> map;
        for(int i = 0; i < fileList->size(); i++)
            map.insert(i, fileList->at(i)->created()); // Created

        sortList<QDateTime>(fileList, map);
        qInfo() << "Sort list by created";
        break;
    }
    case Order::Modified:
    {
        QMap<int, QDateTime*> map;
        for(int i = 0; i < fileList->size(); i++)
            map.insert(i, fileList->at(i)->modified()); // Modified

        sortList<QDateTime>(fileList, map);
        qInfo() << "Sort list by modified";
        break;
    }
    }
}


void ListSort::direction(FileList* fileList, Direction direction) // static
{
    if(actual_direction == direction)
        return;

    actual_direction = direction;
    std::reverse(fileList->begin(), fileList->end());
    qInfo() << "Direction changed";
}


void ListSort::score(FileList* fileList)
{
    QMap<int, double*> map;
    for(int i = 0; i < fileList->size(); i++)
    {
        ImagePtr file = fileList->at(i).staticCast<ImageFile>();
        map.insert(i, file->score()); // Score
    }

    sortList<double>(fileList, map);
    qInfo() << "Sort list by score";
}


template <class T> void ListSort::sortList(FileList* fileList, QMap<int, T*> &map) // static
{
    // Remove duplicates
    QSet<T*> set;
    foreach(T* value, map.values())
        set.insert(value);
    QList<T*> list;
    foreach(T* value, set)
        list.append(value);

    // Sort
    std::sort(list.begin(), list.end(), sortFunction<T>);
    FileList newList;
    foreach(T *value, list)
    {
        QList<int> indexList = map.keys(value);
        foreach(int i, indexList)
            newList.append(fileList->at(i));
    }

    // Update vector
    fileList->swap(newList);
}


template <class T> bool ListSort::sortFunction(T *left, T *right) // static
{
    bool state;
    switch(actual_direction)
    {
    case Direction::Up:
        state = *left < *right;
        break;
    case Direction::Down:
        state = *left > *right;
        break;
    }

    return state;
}


void ListSort::showList(FileList* fileList) // static
{
    for(int i = 0; i < fileList->size(); i++)
        qInfo() << *fileList->at(i)->name();
}
