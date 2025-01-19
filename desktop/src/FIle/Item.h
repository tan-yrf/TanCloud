#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QString>
#include <QHash>
#include <QImage>
#include <QVariant>

enum FileType {
    dir = 0,
    doc = 1,
    image = 2,
    unknow = -1
};

class Item : public QObject{
    Q_OBJECT
public:
    Item(QObject* parent = nullptr);

    QVariant data(int role) const;
    bool setData(int role, const QVariant& value);

    FileType type() const;
    void setType(FileType type);

    bool checkState()const;
    void setCheckState(bool state);

    QString path() const;
    void setPath(const QString& path);

    QImage icon() const;
    void setIcon(const QImage& image);

    QString name() const;
    void setName(const QString& name);

    qint64 size() const;
    void setSize(qint64 size);

    qint64 modifyTime()const;
    void setModifyTime(qint64 time);

    qint64 createTime() const;
    void setCreateTime(qint64 time);
private:
    QHash<int, QVariant> m_data;
};

#endif // ITEM_H
