#ifndef MENU_H
#define MENU_H

#include <QFrame>

namespace Ui {
class Menu;
}

class Menu : public QFrame
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
