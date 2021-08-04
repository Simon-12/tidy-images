#ifndef LISTSORT_H
#define LISTSORT_H

#include <QObject>
#include <QDebug>

#include "basefile/imagefile.h"
#include "settings.h"
#include "options.h"

/*!
 * \brief The ListSort class:
 * Static functions to sort the file list.
 */
class ListSort
{

public:    

    static Order actual_order;
    static Direction actual_direction;

    static void order(FileList* fileList, Order order);
    static void direction(FileList* fileList, Direction direction);
    static void score(FileList* fileList);
    void static showList(FileList* fileList);

private:

    template <class T> static void sortList(FileList* fileList, QMap<int, T*> &map);
    template <class T> static bool sortFunction(T *left, T *right);

    explicit ListSort()
    {
    }
};

#endif // LISTSORT_H
