#include "Home.h"
#include "ui_Home.h"

Home::Home(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
}

Home::~Home()
{
    delete ui;
}

void Home::root() const {
    ui->explorer->cd("");
}
