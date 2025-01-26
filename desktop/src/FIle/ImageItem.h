#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QFrame>

#include "Model.h"

namespace Ui {
class ImageItem;
}

class ImageItem : public QFrame
{
    Q_OBJECT

public:
    explicit ImageItem(QWidget *parent = nullptr, Model* model = nullptr);
    ~ImageItem();

    void check();

protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    Ui::ImageItem *ui;
    Model* m_model = nullptr;
    int m_index = -1;
};

#endif // IMAGEITEM_H
