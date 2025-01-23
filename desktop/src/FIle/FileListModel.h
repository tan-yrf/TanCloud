#ifndef FileListModel_H
#define FileListModel_H

#include <QObject>
#include <QMap>

#include "FileListItem.h"

class FileListModel : public QObject {
    Q_OBJECT
public:
    explicit FileListModel();

    int count() const;

public:
    FileListItem at(int index) const;
    void append(const FileListItem& item);
    void appendList(const QVector<FileListItem>& items);
    void clear();

signals:
    void dataChanged();

private:
    QVector<FileListItem> m_items;
};

#endif // FileListModel_H
