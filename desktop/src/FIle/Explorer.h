#ifndef EXPLORER_H
#define EXPLORER_H

#include <QFrame>
#include <QGridLayout>

#include "Model.h"
#include "Menu.h"
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
    void checkAll(bool state);
    void refresh();
    void update();
    void cd(const QString& path);
    void back();
    bool createFolder(QString& message, const QString& folder_name);
    bool deleteSelected(QString& message);
signals:
    void pathChanged(QString path);
    void countChanged(int selected, int sum);
protected:
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
private:
    bool isImage(const QString& file_name) const;
    void check(QPointF position);
    void entery(QPointF position);
private slots:
    void onCheckedChanged();
    void onRename(QString name);
private:
    Ui::Explorer *ui;
    Model m_model;
    QGridLayout* m_layout = nullptr;
    QString m_current_path;
    enum Pattern {
        List,
        Image
    };
    Pattern m_pattern = Pattern::List;
    Menu m_menu;
};

#endif // EXPLORER_H
