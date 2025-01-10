#ifndef SIDEBUTTON_H
#define SIDEBUTTON_H

/*
 * 这个类是自定义的侧边栏按钮，可以设置普通样式和高亮状态下的图标，以及按钮文字。
 */
#include <QWidget>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QLabel>
class SideButton : public QWidget
{
    Q_OBJECT
public:
    explicit SideButton(QWidget *parent = nullptr);
    void init(const QString& common, const QString& hight_light, const QString& text);
    void setIconSize(int width, int height);
    void common();
    void selected();

protected:
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void clicked();

private:
    void setBtnIcon();

private:
    QPixmap m_common_icon;
    QPixmap m_high_light_icon;

    QVBoxLayout m_layout;
    QLabel m_btn;
    QLabel m_label;

    QString m_common_label;
    QString m_high_light_label;

    bool flag = false;
};

#endif // SIDEBUTTON_H
