#include "Item.h"
#include "ItemRole.h"


Item::Item(QObject *parent) : QObject(parent) {
    setData(ItemRole::CheckState, false);

}

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

void Item::setType(FileType type) {
    switch (type) {
    case dir:
        setData(ItemRole::Type, 0);
        break;
    case doc:
        setData(ItemRole::Type, 1);
        break;
    case image:
        setData(ItemRole::Type, 2);
        break;
    case unknow:
        setData(ItemRole::Type, -1);
        break;
    }
}

bool Item::checkState() const {
    return data(ItemRole::CheckState).toBool();
}

void Item::setCheckState(bool state) {
    setData(ItemRole::CheckState, state);
}

QString Item::path() const {
    return data(ItemRole::Path).toString();
}

void Item::setPath(const QString &path){
    setData(ItemRole::Path, path);
}

QImage Item::icon() const {
    return data(ItemRole::Icon).value<QImage>();
}

void Item::setIcon(const QImage &image) {
    setData(ItemRole::Icon, QVariant::fromValue(image));
}

QString Item::name() const {
    return data(ItemRole::Name).toString();
}

void Item::setName(const QString &name) {
    setData(ItemRole::Name, name);
}

qint64 Item::size() const {
    return data(ItemRole::Size).toLongLong();
}

void Item::setSize(qint64 size) {
    setData(ItemRole::Size, size);
}

qint64 Item::modifyTime() const {
    return data(ItemRole::ModifyTime).toLongLong();
}

void Item::setModifyTime(qint64 time) {
    setData(ItemRole::ModifyTime, time);
}

FileType Item::type() const {
    switch (data(ItemRole::Type).toInt()) {
    case 0:
        return FileType::dir;
    case 1:
        return FileType::doc;
    case 2:
        return FileType::image;
    default:
        return FileType::unknow;
    }
}

qint64 Item::createTime() const {
    return data(ItemRole::CreateTime).toLongLong();
}

void Item::setCreateTime(qint64 time) {
    setData(ItemRole::CreateTime, time);
}


