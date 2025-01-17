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
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onLoginSuccess() {
    this->show();
}
