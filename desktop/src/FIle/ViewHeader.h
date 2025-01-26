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

    void setListPattern();
    void setImagePattern();

private:
    Ui::ViewHeader *ui;
    enum Pattern{
        List,
        Image
    };
    Pattern m_pattern = Pattern::List;
};

#endif // VIEWHEADER_H
