#ifndef VIEW_H
#define VIEW_H

#include <QListView>

#include "Model.h"

class View : public QListView {
    Q_OBJECT
public:
    View(QWidget* parent = nullptr);

private:
    Model m_model;

};

#endif // VIEW_H
