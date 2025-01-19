#include "Model.h"

Model::Model(QObject *parent) : QAbstractItemModel(parent) {

}

QModelIndex Model::index(int row, int colum, const QModelIndex &parent) const {
    if (row < 0 || row >= m_items.count())
        return QModelIndex();
    return createIndex(row, 0, m_items.at(row));
}

QModelIndex Model::parent(const QModelIndex &child) const {
    return QModelIndex(); // 没有父项
}

int Model::rowCount(const QModelIndex &parent) const {
    return m_items.count();
}

int Model::columnCount(const QModelIndex &parent) const {
    return 1;           // listview 只有一列
}

QVariant Model::data(const QModelIndex &index, int role) const {
    if (index.isValid() == false)
        return QVariant();
    Item* item = static_cast<Item*>(index.internalPointer());
    if (item) {
        return item->data(role);
    }
    return QVariant();
}

bool Model::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() == false)
        return false;
    Item* item = m_items.at(index.row());
    if (item) {
        return item->setData(role, value);
    }
    return false;
}

Qt::ItemFlags Model::flags(const QModelIndex &index) const {
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

Item* Model::itemFromIndex(const QModelIndex &index) {
    if (index.isValid() && index.row() >= 0 && index.row() < m_items.count())
        return m_items.at(index.row());
    return nullptr;
}

FileType Model::type(const QModelIndex &index) {
    Item* item = itemFromIndex(index);
    if (item)
        return item->type();
    return FileType::unknow;
}

bool Model::checkState(const QModelIndex &index) {
    Item* item = itemFromIndex(index);
    if (item)
        return item->checkState();
    return false;
}

QString Model::path(const QModelIndex &index) {
    Item* item = itemFromIndex(index);
    if (item)
        return item->path();
    return QString();
}

QImage Model::icon(const QModelIndex &index) {
    Item* item = itemFromIndex(index);
    if (item)
        return item->icon();
    return QImage();
}

QString Model::name(const QModelIndex &index) {
    Item* item = itemFromIndex(index);
    if (item)
        return item->name();
    return QString();
}

qint64 Model::size(const QModelIndex &index) {
    Item* item = itemFromIndex(index);
    if (item)
        return item->size();
    return -1;
}

qint64 Model::modifyTime(const QModelIndex &index) {
    Item* item = itemFromIndex(index);
    if (item)
        return item->modifyTime();
    return -1;
}

qint64 Model::createTime(const QModelIndex &index) {
    Item* item = itemFromIndex(index);
    if (item)
        return item->createTime();
    return -1;
}




