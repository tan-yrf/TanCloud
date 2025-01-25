#include <QMouseEvent>
#include "FIleItemRole.h"
#include "FileExplorer.h"
#include "ui_FileExplorer.h"

FileExplorer::FileExplorer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileExplorer)
{
    ui->setupUi(this);

    m_model.setParent(this);
    ui->list_view->setModel(&m_model);

    QVector<FileListItem> items;
    for (int i = 0; i < 100; i++) {
        FileListItem item;
        item.setData(ItemRole::CheckBox, false);
        item.setData(ItemRole::Icon, QImage("D:\\code\\TanCloud\\desktop\\resource\\icon\\ico.svg"));
        item.setData(ItemRole::Name, u8"你好");
        item.setData(ItemRole::ModifyTime, QString::number(1737635383362));
        item.setData(ItemRole::Type, 1);
        item.setData(ItemRole::Size, 10240);

        items.append(item);
    }
    m_model.appendList(items);

}

FileExplorer::~FileExplorer()
{
    delete ui;
}

void FileExplorer::setListPattern() {
    ui->list_view->setListPattern();
    ui->header->setListPattern();
}

void FileExplorer::setImagePattern() {
    ui->list_view->setImagePattern();
    ui->header->setImagePattern();
}

void FileExplorer::refresh() {
    ui->list_view->refresh();
}

// 只有右键，并且在view范围中的事件才会触发
void FileExplorer::mousePressEvent(QMouseEvent *event) {
    if (event->button() != Qt::RightButton)
        return QWidget::mousePressEvent(event);
    QPoint pos = ui->list_view->mapFromParent(event->pos());
    if (ui->list_view->rect().contains(pos) == false)
        return QWidget::mousePressEvent(event);

    QPointF global_pos = event->globalPosition();
    m_menu.showAtPosition(global_pos);
    event->accept();
    ui->list_view->check(global_pos);
    return QWidget::mousePressEvent(event);
}

