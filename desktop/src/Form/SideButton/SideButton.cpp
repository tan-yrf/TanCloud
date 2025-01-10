#include "SideButton.h"

SideButton::SideButton(QWidget *parent)
    : QWidget{parent} {

    // 设置布局
    m_layout.addWidget(&m_btn);
    m_layout.addWidget(&m_label);
    setLayout(&m_layout);

    m_layout.setContentsMargins(5, 5, 5, 5);
    m_layout.setSpacing(5);

    // 设置对齐方式为居中
    m_layout.setAlignment(Qt::AlignCenter);  // 使按钮和标签居中

    // 设置初始大小
    m_btn.setFixedSize(25, 25);
    m_label.setFixedSize(25, 25);

    m_common_label = "font-size: 12px; color: black;";
    m_high_light_label = "font-size: 12px; color: #0078D4;";

    m_btn.setStyleSheet("background-color: transparent;");
    m_label.setStyleSheet(m_common_label);
    m_label.setAlignment(Qt::AlignCenter);

}

void SideButton::init(const QString& common, const QString& hight_light, const QString &text) {
    m_common_icon = QPixmap(common);
    m_high_light_icon = QPixmap(hight_light);
    m_label.setText(text);
    flag = false;
    setBtnIcon();
}

void SideButton::setIconSize(int width, int height)
{
    m_btn.setFixedWidth(width);
    m_btn.setFixedHeight(height);
    setBtnIcon();
}

// 切换成普通模式
void SideButton::common()
{
    flag = false;
    setBtnIcon();
    m_label.setStyleSheet(m_common_label);
}

// 切换成被选中的样式
void SideButton::selected()
{
    flag = true;
    setBtnIcon();
    m_label.setStyleSheet(m_high_light_label);
}


// 处理鼠标点击事件,点击区域内就相当于点击按钮
void SideButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }
}

void SideButton::setBtnIcon()
{
    QSize buttonSize = m_btn.size(); // 获取 QLabel 的尺寸

    if (flag) {
        QPixmap scaled_pixmap = m_high_light_icon.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_btn.setPixmap(scaled_pixmap); // 设置缩放后的图片
    } else {
        QPixmap scaled_pixmap = m_common_icon.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_btn.setPixmap(scaled_pixmap); // 设置缩放后的图片
    }
}

