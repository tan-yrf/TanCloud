#include <QDateTime>

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
    ui->check_box->setChecked(false);

    QPixmap pixmap = QPixmap::fromImage(item.data(ItemRole::Icon).value<QImage>()).scaled(ui->image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->image->setPixmap(pixmap);

    ui->lab_name->setText(item.data(ItemRole::Name).toString());

    // 毫秒级时间戳
    qint64 modify_timestamp = item.data(ItemRole::ModifyTime).toString().toLongLong();
    QDateTime date_time;
    date_time.setMSecsSinceEpoch(modify_timestamp);
    ui->lab_modify_time->setText(date_time.toString("yyyy-MM-dd"));

    QString type_text = fileTypeIntToString(item.data(ItemRole::Type).toInt());
    ui->lab_type->setText(type_text);

    qint64 size = item.data(ItemRole::Size).toString().toLongLong();
    QString size_text;
    const qint64 GB = 1024LL * 1024 * 1024;
    const qint64 MB = 1024LL * 1024;
    const qint64 KB = 1024LL;
    if (size < GB) {
        if (size < MB) {
            double s = size / KB;
            size_text += QString("%1%2").arg(s, 0, 'f', 1).arg("KB");
        } else {
            double s = size / MB;
            size_text += QString("%1%2").arg(s, 0, 'f', 1).arg("MB");
        }
    } else {
        double s = size / GB;
        size_text += QString("%1%2").arg(s, 0, 'f', 1).arg("G");
    }
    ui->lab_size->setText(size_text);

    // 默认隐藏复选框，只有鼠标悬浮和勾选复选框时才显示
    ui->check_box->setVisible(false);
}

ListItem::~ListItem() {
    delete ui;
}

void ListItem::setChecked(bool state) {
    ui->check_box->setChecked(state);
}

int ListItem::index() const {
    return m_index;
}

void ListItem::enterEvent(QEnterEvent *event) {
    ui->check_box->setVisible(true);
}

void ListItem::leaveEvent(QEvent *event) {
    ui->check_box->setVisible(ui->check_box->checkState());
}

void ListItem::on_check_box_stateChanged(int state) {
    bool res = false;
    if (state == Qt::Checked) {
        ui->check_box->setVisible(true);
        res = true;
    } else {
        ui->check_box->setVisible(false);
    }
    if (m_model){
        m_model->setData(m_index, ItemRole::CheckState, res);
        m_model->checkedChanged();
    }
}

