#ifndef RIGHTMENU_H
#define RIGHTMENU_H

#include <QFrame>

namespace Ui {
class RightMenu;
}

class RightMenu : public QFrame
{
    Q_OBJECT

public:
    explicit RightMenu(QWidget *parent = nullptr);
    ~RightMenu();

    void showAtPosition(QPointF pos);
private:
    Ui::RightMenu *ui;
};

#endif // RIGHTMENU_H
