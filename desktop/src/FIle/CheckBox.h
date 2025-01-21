#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QCheckBox>

class CheckBox : public QCheckBox {
public:
    CheckBox(QWidget *parent = nullptr);

    void setCurrentSize(const QSize &size);
};

#endif // CHECKBOX_H
