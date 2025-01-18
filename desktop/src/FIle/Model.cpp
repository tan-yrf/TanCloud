#include "Model.h"

#include "Item.h"


Model::Model() {
    m_headers << u8"  "<< u8"文件名" << u8"大小" << u8"文件类型" << u8"修改时间";
}


int Model::rowCount(const QModelIndex &parent) const {
    return parent.isValid()? 0 : m_items.count();
}

int Model::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : m_headers.count();
}

QVariant Model::data(const QModelIndex &index, int role) const {
    if (index.isValid() == false)
        return QVariant();

    const Item& item = m_items.at(index.row());

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return item.selecteState()? u8"√": "";
            break;
        case 1:
            return item.name();
            break;
        case 2:
            return item.size();
            break;
        case 3:
            return item.type();
            break;
        case 4:
            return item.lastModifyTime();
            break;
        default:
            break;
        }
    } else if (role == Qt::CheckStateRole && index.column() == 0) {
        return item.selecteState() ? Qt::Checked : Qt::Unchecked;
    }

    return QVariant();
}

bool Model::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() == false)
        return false;

    Item& item = m_items[index.row()];

    if (role == Qt::CheckStateRole && index.column() == 0) {
        bool state = (value.toInt() == Qt::Checked);
        item.setSelectState(state);
        emit dataChanged(index, index);     // 更新视图
        return true;
    }

    return false;
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_headers.at(section);
    }
    return QVariant();
}

QModelIndex Model::index(int row, int column, const QModelIndex &parent) const {
    if (parent.isValid() == false) {
        return createIndex(row, column);
    }
    return QModelIndex();
}

QModelIndex Model::parent(const QModelIndex &index) const {
    return QModelIndex();
}

Qt::ItemFlags Model::flags(const QModelIndex &index) const {
    Qt::ItemFlags default_flags = QAbstractItemModel::flags(index);

    if (index.column() == 0) {  // 复选框
        return default_flags | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    }

    return default_flags | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
