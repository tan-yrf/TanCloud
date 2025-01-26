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

void Home::root() {
    ui->explorer->cd("");
}

void Home::on_list_clicked() {
    ui->explorer->setListPattern();
}



void Home::on_image_clicked() {
    ui->explorer->setImagePattern();
}


void Home::on_refresh_clicked() {
    ui->explorer->refresh();
}

