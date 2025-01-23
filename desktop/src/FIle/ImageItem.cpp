#include "FIleItemRole.h"
#include "ImageItem.h"
#include "ui_ImageItem.h"

ImageItem::ImageItem(QWidget *parent, const FileListItem &item)
    : MetaItem(parent)
    , ui(new Ui::ImageItem) {
    ui->setupUi(this);

    ui->check_box->setChecked(item.data(ItemRole::CheckBox).toBool());

    QPixmap pixmap = QPixmap::fromImage(item.data(ItemRole::Icon).value<QImage>()).scaled(ui->image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->image->setPixmap(pixmap);

    ui->lab_name->setText(item.data(ItemRole::Name).toString());
}

ImageItem::~ImageItem()
{
    delete ui;
}

int ImageItem::width() const {
    return QWidget::width();
}

