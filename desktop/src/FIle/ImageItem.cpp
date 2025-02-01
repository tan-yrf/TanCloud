#include "ImageItem.h"
#include "ui_ImageItem.h"

ImageItem::ImageItem(QWidget *parent, Model *model, int index)
    : QFrame(parent)
    , ui(new Ui::ImageItem) {
    ui->setupUi(this);

    if (model == nullptr || index < 0 || index > model->count())
        return;
    m_model = model;
    m_index = index;

    Item item = model->at(index);
    ui->check_box->setChecked(false);

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

void ImageItem::check(){
    ui->check_box->setChecked(true);
}

int ImageItem::index() const {
    return m_index;
}

void ImageItem::enterEvent(QEnterEvent *event) {
    ui->check_box->setVisible(true);
}

void ImageItem::leaveEvent(QEvent *event) {
    ui->check_box->setVisible(ui->check_box->checkState());
}

void ImageItem::on_check_box_stateChanged(int state) {
    bool res = false;
    if (state == Qt::Checked) {
        ui->check_box->setVisible(true);
    } else {
        ui->check_box->setVisible(false);
    }
    if (m_model){
        m_model->setData(m_index, ItemRole::CheckState, res);
        m_model->countChanged();
    }
}

