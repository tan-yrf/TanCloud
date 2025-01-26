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

void Home::on_btn_pattern_clicked() {
    if (m_pattern == Pattern::List) {
        ui->explorer->setImagePattern();
        m_pattern = Pattern::Image;
        ui->btn_pattern->setIcon(QIcon(":/FIle/cell.svg"));
        ui->btn_pattern->setToolTip(u8"缩略图");
    } else if(m_pattern == Pattern::Image) {
        ui->explorer->setListPattern();
        m_pattern = Pattern::List;
        ui->btn_pattern->setIcon(QIcon(":/FIle/list.svg"));
        ui->btn_pattern->setToolTip(u8"列表");
    }
}


void Home::on_btn_refresh_clicked() {
    ui->explorer->cd("");
}

