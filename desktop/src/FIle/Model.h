#ifndef MODEL_H
#define MODEL_H

#include <QAbstractItemModel>
#include <QVariant>
#include <QImage>

#include "Item.h"

class Model : public QAbstractItemModel {
    Q_OBJECT
public:
    explicit Model(QObject* parent = nullptr);

    // 通过给定的行和列，返回对应的模型索引
    QModelIndex index(int row, int colum, const QModelIndex& parent = QModelIndex()) const override;

    QModelIndex parent(const QModelIndex& child) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
public:
    Item* itemFromIndex(const QModelIndex& index);  // 根据索引获取item指针
    FileType type(const QModelIndex& index);
    bool checkState(const QModelIndex& index);
    QString path(const QModelIndex& index);
    QImage icon(const QModelIndex& index);
    QString name(const QModelIndex& index);
    qint64 size(const QModelIndex& index);
    qint64 modifyTime(const QModelIndex& index);
    qint64 createTime(const QModelIndex& index);

private:
    QVector<Item*> m_items;
};

#endif // MODEL_H
