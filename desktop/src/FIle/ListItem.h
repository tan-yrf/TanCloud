#ifndef LISTITEM_H
#define LISTITEM_H

#include "MetaItem.h"
#include "FileListModel.h"

namespace Ui {
class ListItem;
}

class ListItem : public MetaItem
{
    Q_OBJECT
public:
    explicit ListItem(QWidget *parent = nullptr, FileListModel* model = nullptr, int index = -1);
    ~ListItem();

    void check();

protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

private slots:
    void on_check_box_checkStateChanged(int state);

private:
    Ui::ListItem *ui;
    bool m_selected = false;
    FileListModel* m_model = nullptr;
    int m_index = -1;
};

#endif // LISTITEM_H
