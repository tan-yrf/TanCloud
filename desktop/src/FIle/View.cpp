#include "View.h"
#include "ui_View.h"

View::View(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);
}

View::~View()
{
    delete ui;
}
