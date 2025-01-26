#ifndef MODEL_H
#define MODEL_H

#include <QObject>

#include "Item.h"

class Model : public QObject {
    Q_OBJECT
public:
    explicit Model();

    int count() const;
    Item at(int index) const;
    void append(const Item& item);
    void appendList(const QVector<Item>& items);
    void clear();
    bool setData(int index, int role, const QVariant& value);
    void resetAllCheckBoxState();
signals:
    void dataChanged();
private:
    QVector<Item> m_items;
};

#endif // MODEL_H
