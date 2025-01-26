#include "Item.h"

Item::Item() {}

QVariant Item::data(int role) const {
    if (role < 0 || m_data.contains(role) == false)
        return QVariant();
    return m_data[role];
}

bool Item::setData(int role, const QVariant &value) {
    if (role < 0 || value.isNull())
        return false;

    if (m_data.contains(role) && m_data[role] == value)
        return false;

    m_data[role] = value;
    return true;
}
