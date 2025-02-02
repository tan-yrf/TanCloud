#include "Menu.h"
#include "ui_Menu.h"

Menu::Menu(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}
