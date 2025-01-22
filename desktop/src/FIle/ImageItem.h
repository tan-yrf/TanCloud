#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QFrame>

namespace Ui {
class ImageItem;
}

class ImageItem : public QFrame
{
    Q_OBJECT

public:
    explicit ImageItem(QWidget *parent = nullptr);
    ~ImageItem();

private:
    Ui::ImageItem *ui;
};

#endif // IMAGEITEM_H
