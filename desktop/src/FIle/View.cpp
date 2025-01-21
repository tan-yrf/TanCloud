#include "View.h"

View::View(QWidget *parent) : QListView(parent) {

}

void View::appendItem(Item *item) {
    m_model.appendItem(item);

}

void View::clear() {
    m_model.clear();
}
