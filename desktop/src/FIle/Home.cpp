#include "Home.h"
#include "ui_Home.h"

Home::Home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
}

Home::~Home()
{
    delete ui;
}

void Home::on_list_clicked() {
    ui->explorer->setListPattern();
}



void Home::on_image_clicked() {
    ui->explorer->setImagePattern();
}

