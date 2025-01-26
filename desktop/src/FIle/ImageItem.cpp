#include "ImageItem.h"
#include "ui_ImageItem.h"

ImageItem::ImageItem(QWidget *parent, Model *model, int index)
    : QFrame(parent)
    , ui(new Ui::ImageItem)
{
    ui->setupUi(this);
}

ImageItem::~ImageItem()
{
    delete ui;
}
