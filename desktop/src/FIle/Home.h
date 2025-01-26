#ifndef HOME_H
#define HOME_H

#include <QFrame>

namespace Ui {
class Home;
}

class Home : public QFrame
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();

    void root() const;

private slots:
    void on_list_clicked();

    void on_image_clicked();

private:
    Ui::Home *ui;
};

#endif // HOME_H
