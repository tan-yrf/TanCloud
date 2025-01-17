#include "SideBar.h"
#include "ui_SideBar.h"

SideBar::SideBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SideBar) {
    ui->setupUi(this);

    QPalette palette(this->palette());
    palette.setColor(QPalette::Window, QColor(245, 247, 250));
    this->setPalette(palette);
    this->setAutoFillBackground(true);

    // 普通状态样式
    m_common_style = "QToolButton {"
                     "    background-color: rgb(245, 247, 250);"
                     "    color: #1f2026;"
                     "    border: none;"
                     "    border-radius: 10px;"
                     "    padding: 5px;"
                     "}"
                     "QToolButton:hover {"
                     "    background-color: rgb(235, 237, 241);"
                     "}";

    // 选中状态样式
    m_selected_style = "QToolButton {"
                       "    background-color: rgb(245, 247, 250);"
                       "    color: #0d53fd;"
                       "    border: none;"
                       "    border-radius: 10px;"
                       "    padding: 5px;"
                       "}"
                       "QToolButton:hover {"
                       "    background-color: rgb(235, 237, 241);"
                       "}";
}

SideBar::~SideBar() {
    delete ui;
}

void SideBar::on_btn_file_clicked() {
    ui->btn_file->setIcon(QIcon(":/folder_selected.svg"));
    ui->btn_file->setStyleSheet(m_selected_style);

    ui->btn_transfer->setIcon(QIcon(":/transfer_common.svg"));
    ui->btn_transfer->setStyleSheet(m_common_style);

    ui->btn_share->setIcon(QIcon(":/share_common.svg"));
    ui->btn_share->setStyleSheet(m_common_style);
}


void SideBar::on_btn_transfer_clicked() {
    ui->btn_file->setIcon(QIcon(":/folder_common.svg"));
    ui->btn_file->setStyleSheet(m_common_style);

    ui->btn_transfer->setIcon(QIcon(":/transfer_selected.svg"));
    ui->btn_transfer->setStyleSheet(m_selected_style);

    ui->btn_share->setIcon(QIcon(":/share_common.svg"));
    ui->btn_share->setStyleSheet(m_common_style);
}


void SideBar::on_btn_share_clicked() {
    ui->btn_file->setIcon(QIcon(":/folder_common.svg"));
    ui->btn_file->setStyleSheet(m_common_style);

    ui->btn_transfer->setIcon(QIcon(":/transfer_common.svg"));
    ui->btn_transfer->setStyleSheet(m_common_style);

    ui->btn_share->setIcon(QIcon(":/share_selected.svg"));
    ui->btn_share->setStyleSheet(m_selected_style);
}

