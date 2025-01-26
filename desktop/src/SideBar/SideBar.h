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

    // 显示云空间大小，如果已经使用的空间不足GB，就以M为单位，超过G就以G为单位
    void updateSpaceSize();

signals:
    void switchFile();
    void switchTransfer();
    void switchShare();

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
