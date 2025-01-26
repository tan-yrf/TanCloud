#ifndef HOME_H
#define HOME_H

#include <QWidget>

namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();

private slots:
    void on_list_clicked();

    void on_image_clicked();

    void on_refresh_clicked();

private:
    Ui::Home *ui;
};

#endif // HOME_H
