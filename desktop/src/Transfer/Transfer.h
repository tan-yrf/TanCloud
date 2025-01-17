#ifndef TRANSFER_H
#define TRANSFER_H

#include <QWidget>

namespace Ui {
class Transfer;
}

class Transfer : public QWidget
{
    Q_OBJECT

public:
    explicit Transfer(QWidget *parent = nullptr);
    ~Transfer();

private:
    Ui::Transfer *ui;
};

#endif // TRANSFER_H
