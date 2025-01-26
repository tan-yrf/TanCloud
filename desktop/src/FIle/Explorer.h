#ifndef EXPLORER_H
#define EXPLORER_H

#include <QFrame>

#include "Model.h"
namespace Ui {
class Explorer;
}

class Explorer : public QFrame
{
    Q_OBJECT

public:
    explicit Explorer(QWidget *parent = nullptr);
    ~Explorer();

    void setListPattern();
    void setImagePattern();
    void check(QPointF position);
    void refresh();
    void update();
    void cd(const QString& path);

private:
    bool isImage(const QString& file_name) const;
private:
    Ui::Explorer *ui;
    Model m_model;
    QString m_current_path;
    enum Pattern {
        List,
        Image
    };
    Pattern m_pattern = Pattern::List;
};

#endif // EXPLORER_H
