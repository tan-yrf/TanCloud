#include "ListItem.h"
#include "ui_ListItem.h"

ListItem::ListItem(QWidget *parent, Model *model, int index)
    : QFrame(parent)
    , ui(new Ui::ListItem)
{
    ui->setupUi(this);

    if (model == nullptr || index < 0 || index > model->count())
        return;
    m_model = model;
    m_index = index;

    Item item = model->at(index);
    ui->check_box->setChecked(item.data(ItemRole::CheckBox).toBool());

    QPixmap pixmap = QPixmap::fromImage(item.data(ItemRole::Icon).value<QImage>()).scaled(ui->image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->image->setPixmap(pixmap);

    ui->lab_name->setText(item.data(ItemRole::Name).toString());

    // 默认隐藏复选框，只有鼠标悬浮和勾选复选框时才显示
    ui->check_box->setVisible(false);
}

ListItem::~ListItem()
{
    delete ui;
}
