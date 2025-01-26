#include "Model.h"

Model::Model() {}

int Model::count() const {
    return m_items.count();
}

Item Model::at(int index) const {
    return m_items.at(index);
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
    if (index < 0 || index > m_items.count())
        return false;
    return m_items[index].setData(role, value);
}
