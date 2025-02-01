#include "Model.h"

Model::Model() {}

int Model::count() const {
    return m_items.count();
}

bool Model::indexIsValid(int index) const {
    if (index >= 0 && index < m_items.size())
        return true;
    return false;
}

Item Model::at(int index) const {
    if (indexIsValid(index))
        return m_items.at(index);
    return Item();
}

void Model::append(const Item &item) {
    m_items.append(item);
    emit dataChanged();
}

void Model::appendList(const QVector<Item> &items) {
    for (const auto& item : items) {
        m_items.append(item);
    }
    emit dataChanged();
}

void Model::clear() {
    if (m_items.isEmpty())
        return;
    m_items.clear();
    emit dataChanged();
}

bool Model::setData(int index, int role, const QVariant &value) {
    if (indexIsValid(index))
        return m_items[index].setData(role, value);
    return false;
}

void Model::resetAllCheckBoxState() {
    for (auto& item : m_items) {
        item.setData(ItemRole::CheckState, false);
    }
}

QVector<Item> Model::getSelectedItems() const {
    QVector<Item> items;
    for (const auto& item : m_items) {
        if (item.data(ItemRole::CheckState).toBool() == true)
            items.append(item);
    }
    return items;
}
