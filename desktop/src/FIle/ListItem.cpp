#include <QDateTime>

#include "ListItem.h"
#include "ui_ListItem.h"
#include "FileType.h"
#include "FileItemRole.h"

ListItem::ListItem(QWidget *parent, const FileListItem &item)
    : MetaItem(parent)
    , ui(new Ui::ListItem)
{
    ui->setupUi(this);

    ui->check_box->setChecked(item.data(ItemRole::CheckBox).toBool());

    QPixmap pixmap = QPixmap::fromImage(item.data(ItemRole::Icon).value<QImage>());
    ui->image->setPixmap(pixmap);

    ui->lab_name->setText(item.data(ItemRole::Name).toString());

    // 毫秒级时间戳
    qint64 modify_timestamp = item.data(ItemRole::ModifyTime).toString().toLongLong();
    QDateTime date_time;
    date_time.setMSecsSinceEpoch(modify_timestamp);
    ui->lab_modify_time->setText(date_time.toString("yyyy-MM-dd"));

    QString type_text = fileTypeIntToString(item.data(ItemRole::Type).toInt());
    ui->lab_type->setText(type_text);

    qint64 size = item.data(ItemRole::Size).toLongLong();
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
}

ListItem::~ListItem() {
    delete ui;
}
