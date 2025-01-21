#include "CheckBox.h"

CheckBox::CheckBox(QWidget *parent) : QCheckBox(parent) {}

void CheckBox::setCurrentSize(const QSize &size) {
    setFixedSize(size);
    QString style_sheet = QString(
                              "QCheckBox::indicator {"
                              "   border-radius: 2px;"
                              "   border: 1px solid #b1b1b1;"
                              "   width: %1px;"
                              "   height: %2px;"
                              "} "
                              "QCheckBox::checked {"
                              "   border-radius: 2px;"
                              "   border: 0px solid #b1b1b1;"
                              "   border-image: url(:/check_box.svg);"
                              "}"
                              ).arg(size.width() - 2).arg(size.height() - 2);
    setStyleSheet(style_sheet);
}
