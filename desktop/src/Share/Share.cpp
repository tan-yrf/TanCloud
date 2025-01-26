#include "Share.h"
#include "ui_Share.h"

Share::Share(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Share)
{
    ui->setupUi(this);
}

Share::~Share()
{
    delete ui;
}
