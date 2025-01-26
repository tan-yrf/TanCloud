#ifndef FILELISTITEM_H
#define FILELISTITEM_H

#include <QHash>
#include <QVariant>

class FileListItem {
public:
    explicit FileListItem();

    QVariant data(int role) const;
    bool setData(int role, const QVariant& value);
private:
    QHash<int, QVariant> m_data;
};

#endif // FILELISTITEM_H
