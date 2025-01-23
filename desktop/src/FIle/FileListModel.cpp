#include "FileListModel.h"

FileListModel::FileListModel() {}

int FileListModel::count() const {
    return m_items.count();
}

FileListItem FileListModel::at(int index) const {
    return m_items.at(index);
}


void FileListModel::append(const FileListItem &item) {
    m_items.append(item);
    emit dataChanged();
}

void FileListModel::appendList(const QVector<FileListItem> &items) {
    for (const auto& item : items) {
        m_items.append(item);
    }
    emit dataChanged();
}

void FileListModel::clear() {
    if (m_items.isEmpty())
        return;
    m_items.clear();
    emit dataChanged();
}
