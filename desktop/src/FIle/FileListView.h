#ifndef FILELISTVIEW_H
#define FILELISTVIEW_H

#include <QFrame>

#include "FileListModel.h"
namespace Ui {
class FileListView;
}

class FileListView : public QFrame
{
    Q_OBJECT

public:
    explicit FileListView(QWidget *parent = nullptr);
    ~FileListView();

    void setModel(FileListModel* model);
    void setListPattern();
    void setImagePattern();
    void refresh();
    void check(QPointF position);

private:
    void update();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::FileListView *ui;
    FileListModel* m_model = nullptr;
    enum Pattern{
        List,
        Image
    };
    Pattern m_pattern = Pattern::List;
};

#endif // FILELISTVIEW_H
