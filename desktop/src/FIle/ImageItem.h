#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include "MetaItem.h"
#include "FileListItem.h"

namespace Ui {
class ImageItem;
}

class ImageItem : public MetaItem
{
    Q_OBJECT

public:
    explicit ImageItem(QWidget *parent = nullptr, const FileListItem& item = FileListItem());
    ~ImageItem();

    int width() const;

private:
    Ui::ImageItem *ui;
};

#endif // IMAGEITEM_H
