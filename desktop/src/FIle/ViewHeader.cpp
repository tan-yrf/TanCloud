#include "ViewHeader.h"
#include "ui_ViewHeader.h"

ViewHeader::ViewHeader(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewHeader)
{
    ui->setupUi(this);
}

ViewHeader::~ViewHeader()
{
    delete ui;
}
