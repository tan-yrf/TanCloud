#ifndef LISTITEM_H
#define LISTITEM_H

#include "MetaItem.h"
#include "FileListItem.h"

namespace Ui {
class ListItem;
}

class ListItem : public MetaItem
{
    Q_OBJECT
public:
    explicit ListItem(QWidget *parent = nullptr, const FileListItem& item = FileListItem());
    ~ListItem();

private:
    Ui::ListItem *ui;
};

#endif // LISTITEM_H
