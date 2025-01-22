#ifndef LISTITEM_H
#define LISTITEM_H

#include <QFrame>

namespace Ui {
class ListItem;
}

class ListItem : public QFrame
{
    Q_OBJECT

public:
    explicit ListItem(QWidget *parent = nullptr);
    ~ListItem();

private:
    Ui::ListItem *ui;
};

#endif // LISTITEM_H
