#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QFrame>
#include <QEnterEvent>
#include <QEvent>

#include "Model.h"

namespace Ui {
class ImageItem;
}

class ImageItem : public QFrame
{
    Q_OBJECT

public:
    explicit ImageItem(QWidget *parent = nullptr, Model* model = nullptr, int index = -1);
    ~ImageItem();

    void setChecked(bool state);
    int index() const;
protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

private slots:
    void on_check_box_stateChanged(int arg1);

private:
    Ui::ImageItem *ui;
    Model* m_model = nullptr;
    int m_index = -1;
};

#endif // IMAGEITEM_H
