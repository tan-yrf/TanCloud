#include "Item.h"

Item::Item() {}

QString Item::path() const {
    return m_path;
}

QString Item::name() const {
    return m_name;
}

qint64 Item::size() const {
    return m_size;
}

bool Item::selecteState() const {
    return m_selected;
}

qint64 Item::createTime() const {
    return m_create_time;
}

qint64 Item::lastModifyTime() const {
    return m_last_modify_time;
}

FileType Item::type() const {
    return m_type;
}

void Item::setSelectState(bool state) {
    m_selected = state;
}
