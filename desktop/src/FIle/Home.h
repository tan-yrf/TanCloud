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

private:
    Ui::Home *ui;
};

#endif // HOME_H
