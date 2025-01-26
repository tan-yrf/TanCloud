#include "FIleItemRole.h"
#include "ImageItem.h"
#include "ui_ImageItem.h"
#include "FileListItem.h"

ImageItem::ImageItem(QWidget *parent, FileListModel *model, int index)
    : MetaItem(parent)
    , ui(new Ui::ImageItem) {
    ui->setupUi(this);

    if (model == nullptr || index < 0 || index > model->count())
        return;
    m_model = model;
    m_index = index;

    FileListItem item = model->at(index);
    ui->check_box->setChecked(item.data(ItemRole::CheckBox).toBool());

    QPixmap pixmap = QPixmap::fromImage(item.data(ItemRole::Icon).value<QImage>()).scaled(ui->image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->image->setPixmap(pixmap);

    ui->lab_name->setText(item.data(ItemRole::Name).toString());

    // 默认隐藏复选框，只有鼠标悬浮和勾选复选框时才显示
    ui->check_box->setVisible(false);
}

ImageItem::~ImageItem()
{
    delete ui;
}

int ImageItem::width() const {
    return QWidget::width();
}

void ImageItem::check() {
    ui->check_box->setChecked(true);
}

void ImageItem::enterEvent(QEnterEvent *event) {
    ui->check_box->setVisible(true);
}

void ImageItem::leaveEvent(QEvent *event) {
    ui->check_box->setVisible(ui->check_box->checkState());
}

void ImageItem::on_check_box_checkStateChanged(int state) {
    if (state == Qt::Checked) {
        ui->check_box->setVisible(true);
        emit checkBoxStateChanged(true);
    } else {
        ui->check_box->setVisible(false);
        emit checkBoxStateChanged(false);
    }
}

