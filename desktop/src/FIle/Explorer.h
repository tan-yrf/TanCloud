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

    void refresh();
    void update();
    void cd(const QString& path);
    void back();
    bool createFolder(QString& message, const QString& folder_name);
    bool deleteSelected(QString& message);
signals:
    void pathChanged(QString path);
protected:
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
private:
    bool isImage(const QString& file_name) const;
    void check(QPointF position);
    void entery(QPointF position);
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
