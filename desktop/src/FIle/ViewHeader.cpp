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

void ViewHeader::setListPattern() {
    if (m_pattern == Pattern::List)
        return;
    m_pattern = Pattern::List;
    ui->frame->show();
    ui->text->setText(u8"名称");
}

void ViewHeader::setImagePattern() {
    if (m_pattern == Pattern::Image)
        return;
    m_pattern = Pattern::Image;
    ui->frame->hide();
    ui->text->setText(u8"");
}
