#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include "MetaItem.h"
#include "FileListModel.h"

namespace Ui {
class ImageItem;
}

class ImageItem : public MetaItem
{
    Q_OBJECT

public:
    explicit ImageItem(QWidget *parent = nullptr, FileListModel* model = nullptr, int index = -1);
    ~ImageItem();

    int width() const;
    void check();

protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

private slots:
    void on_check_box_stateChanged(int arg1);

private:
    Ui::ImageItem *ui;
    FileListModel* m_model = nullptr;
    int m_index = -1;
};

#endif // IMAGEITEM_H
