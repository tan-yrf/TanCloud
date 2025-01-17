#ifndef SHARE_H
#define SHARE_H

#include <QWidget>

namespace Ui {
class Share;
}

class Share : public QWidget
{
    Q_OBJECT

public:
    explicit Share(QWidget *parent = nullptr);
    ~Share();

private:
    Ui::Share *ui;
};

#endif // SHARE_H
