#ifndef FILELISTVIEW_H
#define FILELISTVIEW_H

#include <QWidget>
#include <QScrollArea>
#include <QGridLayout>

#include "FileListModel.h"

enum ViewPattern{
    List,
    Image
};

class FileListView : public QWidget {
    Q_OBJECT
public:
    explicit FileListView(QWidget* parent = nullptr);

    void setModel(FileListModel* model);
    void setPattern(ViewPattern pattern);

private slots:
    void update();

private:
    FileListModel* m_model = nullptr;
    QScrollArea m_area;
    QWidget m_content_widget;
    QGridLayout m_layout;

    ViewPattern m_pattern = ViewPattern::List;
};

#endif // FILELISTVIEW_H
