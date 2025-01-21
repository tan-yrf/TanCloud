#ifndef FILE_H
#define FILE_H

#include <QWidget>

#include "View.h"

namespace Ui {
class File;
}

class File : public QWidget
{
    Q_OBJECT

public:
    explicit File(QWidget *parent = nullptr);
    ~File();

    View* view();

private:
    Ui::File *ui;
};

#endif // FILE_H
