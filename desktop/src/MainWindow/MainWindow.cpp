#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QPalette palette(this->palette());
    palette.setColor(QPalette::Window, QColor(255, 255, 255));
    this->setPalette(palette);
    this->setAutoFillBackground(true);

    connect(ui->sidebar, &SideBar::switchFile, [&](){
        ui->widgets->setCurrentWidget(ui->home);
    });

    connect(ui->sidebar, &SideBar::switchTransfer, [&](){
        ui->widgets->setCurrentWidget(ui->transfer);
    });

    connect(ui->sidebar, &SideBar::switchShare, [&](){
        ui->widgets->setCurrentWidget(ui->share);
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onLoginSuccess() {
    this->show();
    ui->sidebar->updateSpaceSize();
    ui->home->root();
}
