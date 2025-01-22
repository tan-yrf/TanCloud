#include "ListItem.h"
#include "ui_ListItem.h"

ListItem::ListItem(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ListItem)
{
    ui->setupUi(this);
}

ListItem::~ListItem()
{
    delete ui;
}
