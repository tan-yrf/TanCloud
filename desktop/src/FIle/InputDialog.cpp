#include "InputDialog.h"
#include "ui_InputDialog.h"

InputDialog::InputDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InputDialog)
{
    ui->setupUi(this);
}

InputDialog::~InputDialog()
{
    delete ui;
}

void InputDialog::on_btn_sure_clicked() {
    emit inputText(ui->edit_text->text());
    accept();
}


void InputDialog::on_btn_cancle_clicked() {
    reject();
}

