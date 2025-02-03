#ifndef MENU_H
#define MENU_H

#include <QFrame>

#include "Model.h"
namespace Ui {
class Menu;
}

class Menu : public QFrame
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    void setModel(Model* model);
    void showAtPosition(const QPointF pos);
protected:
    void focusOutEvent(QFocusEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    bool isFolderNameValid(const QString &folder_name, QString &error_message);

signals:
    void rename(QString name);
private slots:
    void on_btn_rename_clicked();

private:
    Ui::Menu *ui;
    Model* m_model = nullptr;
};

#endif // MENU_H
