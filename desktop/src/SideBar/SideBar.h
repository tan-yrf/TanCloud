#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

namespace Ui {
class SideBar;
}

class SideBar : public QWidget
{
    Q_OBJECT

public:
    explicit SideBar(QWidget *parent = nullptr);
    ~SideBar();

private slots:
    void on_btn_file_clicked();

    void on_btn_transfer_clicked();

    void on_btn_share_clicked();

private:
    Ui::SideBar *ui;
    QString m_common_style;
    QString m_selected_style;
};

#endif // SIDEBAR_H
