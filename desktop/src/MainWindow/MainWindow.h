#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum SideBtnType {
    file,
    transfer,
    share,
    setting
};

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void onSideBtnClicked(SideBtnType type);
    void on_min_clicked();
    void on_max_clicked();
    void on_close_clicked();

private:
    void initSideBar();
    void initWindowStyle();
private:
    Ui::MainWindow *ui;

    bool m_is_dragging;             // 记录鼠标是否正在拖拽
    QPoint m_drag_start_pos;        // 记录鼠标按下的位置
};
#endif // MAINWINDOW_H
