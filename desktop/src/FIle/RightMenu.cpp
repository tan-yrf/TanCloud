#include <QScreen>
#include "RightMenu.h"
#include "ui_RightMenu.h"

RightMenu::RightMenu(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::RightMenu)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Popup);
}

RightMenu::~RightMenu()
{
    delete ui;
}

void RightMenu::showAtPosition(QPointF _pos) {
    QPoint pos = _pos.toPoint();

    QScreen *screen = QApplication::primaryScreen();
    QRect screen_geometry = screen->availableGeometry();

    // 调整菜单位置，确保不会超出屏幕
    if (pos.x() + width() > screen_geometry.right()) {
        pos.setX(screen_geometry.right() - width());
    }
    if (pos.y() + height() > screen_geometry.bottom()) {
        pos.setY(screen_geometry.bottom() - height());
    }

    move(pos);
    show();
}
