#ifndef MODEL_H
#define MODEL_H

#include "Item.h"

class Model
{
public:
    explicit Model();

    Item at(int index) const;
    bool setData(int index, int role, const QVariant& value);
    int count() const;
    void append(const Item& item);
    void appendList(const QVector<Item>& items);
    void clear();

signals:
    void dataChanged();
private:
    QVector<Item> m_items;
};

#endif // MODEL_H
