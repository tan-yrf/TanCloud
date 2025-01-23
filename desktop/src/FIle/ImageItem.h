#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include "MetaItem.h"

namespace Ui {
class ImageItem;
}

class ImageItem : public MetaItem
{
    Q_OBJECT

public:
    explicit ImageItem(QWidget *parent = nullptr);
    ~ImageItem();

private:
    Ui::ImageItem *ui;
};

#endif // IMAGEITEM_H
