#include "Transfer.h"
#include "ui_Transfer.h"

Transfer::Transfer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Transfer)
{
    ui->setupUi(this);
}

Transfer::~Transfer()
{
    delete ui;
}
