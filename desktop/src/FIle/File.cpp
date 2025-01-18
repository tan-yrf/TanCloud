#include "File.h"
#include "ui_File.h"

File::File(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::File)
{
    ui->setupUi(this);
}

File::~File() {
    delete ui;
}
