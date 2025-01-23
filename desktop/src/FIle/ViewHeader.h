#ifndef VIEWHEADER_H
#define VIEWHEADER_H

#include <QWidget>

namespace Ui {
class ViewHeader;
}

class ViewHeader : public QWidget
{
    Q_OBJECT

public:
    explicit ViewHeader(QWidget *parent = nullptr);
    ~ViewHeader();

private:
    Ui::ViewHeader *ui;
};

#endif // VIEWHEADER_H
