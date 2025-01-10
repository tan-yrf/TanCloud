#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QPen>
#include <QPainter>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>
#include <QColor>
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initSideBar();
    initWindowStyle();
    onSideBtnClicked(SideBtnType::file);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    // 调用父类的 resizeEvent 处理默认的行为
    QWidget::resizeEvent(event);

    if (this->isMaximized()) {
        ui->max->setIcon(QIcon(":/MainWindow/window.svg"));
    } else {
        ui->max->setIcon(QIcon(":/MainWindow/max.svg"));
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && ui->top_bar->geometry().contains(event->pos())) {
        m_drag_start_pos = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
    QWidget::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && m_drag_start_pos.isNull() == false) {
        // 如果鼠标左键按下且之前记录了起始位置，就根据鼠标移动的偏移量来移动窗口
        move(event->globalPosition().toPoint() - m_drag_start_pos);
        event->accept();
    }
    QWidget::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_drag_start_pos = QPoint();  // 释放鼠标后，清空记录的位置信息
    QWidget::mouseReleaseEvent(event);
}

void MainWindow::onSideBtnClicked(SideBtnType type)
{
    switch (type) {
    case SideBtnType::file:
        ui->btn_file->selected();
        ui->btn_transfer->common();
        ui->btn_share->common();
        ui->stackedWidget->setCurrentIndex(0);
        break;
    case SideBtnType::transfer:
        ui->btn_file->common();
        ui->btn_transfer->selected();
        ui->btn_share->common();
        ui->stackedWidget->setCurrentIndex(1);
        break;
    case SideBtnType::share:
        ui->btn_file->common();
        ui->btn_transfer->common();
        ui->btn_share->selected();
        ui->stackedWidget->setCurrentIndex(2);
        break;
    default:
        break;
    }
}

// 初始化侧边栏的样式
void MainWindow::initSideBar() {
    ui->btn_file->init(":/MainWindow/folder_common.svg", ":/MainWindow/folder_selected.svg", u8"文件");
    ui->btn_transfer->init(":/MainWindow/transfer_common.svg", ":/MainWindow/transfer_selected.svg", u8"传输");
    ui->btn_share->init(":/MainWindow/share_common.svg", ":/MainWindow/share_selected.svg", u8"分享");
    ui->btn_setting->init(":/MainWindow/setting_common.svg", ":/MainWindow/setting_common.svg", u8"");
    ui->btn_setting->setIconSize(20, 20);

    QPixmap sign(":/MainWindow/cloud.svg");
    QPixmap scale_sign = sign.scaled(ui->sign->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->sign->setPixmap(scale_sign);

    connect(ui->btn_file, &SideButton::clicked, this, [this]{
        onSideBtnClicked(SideBtnType::file);
    });
    connect(ui->btn_transfer, &SideButton::clicked, this, [this]{
        onSideBtnClicked(SideBtnType::transfer);
    });
    connect(ui->btn_share, &SideButton::clicked, this, [this]{
        onSideBtnClicked(SideBtnType::share);
    });
}


// 初始化窗口样式
void MainWindow::initWindowStyle()
{
    this->setWindowFlags(Qt::FramelessWindowHint);              // 仅设置无边框（隐藏标题栏）的窗口标志
    this->setAttribute(Qt::WA_TranslucentBackground, true);     //设置窗体透明

    // 设置阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);                        //设置阴影距离
    shadow->setColor(QColor("#ebebeb"));            //设置阴影颜色
    shadow->setBlurRadius(100);                     //设置阴影模糊半径

    this->setGraphicsEffect(shadow);
}

void MainWindow::on_min_clicked() {
    this->showMinimized();
}

void MainWindow::on_max_clicked() {
    if (this->isMaximized()) {
        this->showNormal();
    } else {
        this->showMaximized();
    }
}

void MainWindow::on_close_clicked() {
    this->close();
}

