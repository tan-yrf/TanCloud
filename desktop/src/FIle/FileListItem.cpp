#include "FileListItem.h"

FileListItem::FileListItem() {}

QVariant FileListItem::data(int role) const {
    if (role < 0 || m_data.contains(role) == false)
        return QVariant();
    return m_data[role];
}

bool FileListItem::setData(int role, const QVariant &value) {
    if (role < 0 || value.isNull())
        return false;

    if (m_data.contains(role) && m_data[role] == value)
        return false;

    m_data[role] = value;
    return true;
}
