#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>

namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = nullptr);
    ~InputDialog();

signals:
    void inputText(QString text);
private slots:
    void on_btn_sure_clicked();
    void on_btn_cancle_clicked();

private:
    Ui::InputDialog *ui;
};

#endif // INPUTDIALOG_H
