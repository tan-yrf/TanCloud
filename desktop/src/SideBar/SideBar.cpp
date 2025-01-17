#include "SideBar.h"
#include "ui_SideBar.h"

#include "UserConfig.h"

SideBar::SideBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SideBar) {
    ui->setupUi(this);

    QPalette palette(this->palette());
    palette.setColor(QPalette::Window, QColor(245, 247, 250));
    this->setPalette(palette);
    this->setAutoFillBackground(true);

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

    on_btn_file_clicked();
}

SideBar::~SideBar() {
    delete ui;
}

void SideBar::updateSpaceSize() {
    const qint64 used_size = UserConfig::used;
    const qint64 total_size = UserConfig::space;

    const qint64 TB = 1024LL * 1024 * 1024 * 1024;
    const qint64 GB = 1024LL * 1024 * 1024;
    const qint64 MB = 1024LL * 1024;

    QString text;
    if (used_size < TB) {
        if (used_size < GB) {
            double used = used_size / MB;
            text += QString("%1%2").arg(used, 0, 'f', 0).arg("M");
        } else {
            double used = used_size / GB;
            text += QString("%1%2").arg(used, 0, 'f', 1).arg("G");
        }
    } else {
        double used = used_size / TB;
        text += QString("%1%2").arg(used, 0, 'f', 1).arg("T");
    }
    text += '/';
    if (total_size < TB) {
        if (total_size < GB) {
            int total = total_size / MB;
            text += QString("%1%2").arg(total).arg("M");
        } else {
            int total = total_size / GB;
            text += QString("%1%2").arg(total).arg("G");
        }
    } else {
        int total = total_size / TB;
        text += QString("%1%2").arg(total).arg("T");
    }
    ui->lab_rate->setText(text);

    if (total_size < 0 || total_size == 0) {
        ui->progress_bar->setValue(0);
        return;
    }

    double rate = used_size * 100  / total_size;
    ui->progress_bar->setValue(rate);
}

void SideBar::on_btn_file_clicked() {
    ui->btn_file->setIcon(QIcon(":/SideBar/folder_selected.svg"));
    ui->btn_file->setStyleSheet(m_selected_style);

    ui->btn_transfer->setIcon(QIcon(":/SideBar/transfer_common.svg"));
    ui->btn_transfer->setStyleSheet(m_common_style);

    ui->btn_share->setIcon(QIcon(":/SideBar/share_common.svg"));
    ui->btn_share->setStyleSheet(m_common_style);

    emit switchFile();
}


void SideBar::on_btn_transfer_clicked() {
    ui->btn_file->setIcon(QIcon(":/SideBar/folder_common.svg"));
    ui->btn_file->setStyleSheet(m_common_style);

    ui->btn_transfer->setIcon(QIcon(":/SideBar/transfer_selected.svg"));
    ui->btn_transfer->setStyleSheet(m_selected_style);

    ui->btn_share->setIcon(QIcon(":/SideBar/share_common.svg"));
    ui->btn_share->setStyleSheet(m_common_style);

    emit switchTransfer();
}


void SideBar::on_btn_share_clicked() {
    ui->btn_file->setIcon(QIcon(":/SideBar/folder_common.svg"));
    ui->btn_file->setStyleSheet(m_common_style);

    ui->btn_transfer->setIcon(QIcon(":/SideBar/transfer_common.svg"));
    ui->btn_transfer->setStyleSheet(m_common_style);

    ui->btn_share->setIcon(QIcon(":/SideBar/share_selected.svg"));
    ui->btn_share->setStyleSheet(m_selected_style);

    emit switchShare();
}

