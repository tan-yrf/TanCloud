#include "FileExplorer.h"
#include "ui_FileExplorer.h"

FileExplorer::FileExplorer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileExplorer)
{
    ui->setupUi(this);
}

FileExplorer::~FileExplorer()
{
    delete ui;
}
