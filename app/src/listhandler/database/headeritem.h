#ifndef HEADERITEM_H
#define HEADERITEM_H

#include <QObject>

#include "options.h"

/*!
 * \brief The HeaderItem class:
 * Item for the header model.
 */
class HeaderItem {
public:
    HeaderItem(QString name) : m_name(name), m_filter(""), m_direction(HeaderDirection::Disabled) {}

    QString name() { return m_name; }
    QString filter() { return m_filter; }
    HeaderDirection direction() { return m_direction; }

    void setFilter(QString filter) { m_filter = filter; }
    void setDirection(HeaderDirection state) { m_direction = state; }

private:
    QString m_name;
    QString m_filter;
    HeaderDirection m_direction;
};

#endif  // HEADERITEM_H
