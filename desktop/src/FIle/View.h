#ifndef VIEW_H
#define VIEW_H

#include <QWidget>

namespace Ui {
class View;
}

class View : public QWidget
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = nullptr);
    ~View();

private:
    Ui::View *ui;
};

#endif // VIEW_H
