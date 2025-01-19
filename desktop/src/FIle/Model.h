#ifndef MODEL_H
#define MODEL_H

#include <QAbstractItemModel>
#include <QVariant>

#include "Item.h"

class Model : public QAbstractItemModel {
    Q_OBJECT
public:
    Model();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

public:
    void addItem(const Item& item);
    void clear();

private:
    QVector<Item> m_items;
    QStringList m_headers;
};

#endif // MODEL_H
