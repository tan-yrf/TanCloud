#ifndef LISTITEM_H
#define LISTITEM_H

#include <QFrame>

#include "Model.h"

namespace Ui {
class ListItem;
}

class ListItem : public QFrame
{
    Q_OBJECT

public:
    explicit ListItem(QWidget *parent = nullptr, Model* model = nullptr, int index = -1);
    ~ListItem();

protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    Ui::ListItem *ui;
    Model* m_model = nullptr;
    int m_index = -1;
};

#endif // LISTITEM_H
