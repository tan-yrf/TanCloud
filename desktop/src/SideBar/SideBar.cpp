#include "SideBar.h"
#include "ui_SideBar.h"

SideBar::SideBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SideBar) {
    ui->setupUi(this);
}

SideBar::~SideBar() {
    delete ui;
}
