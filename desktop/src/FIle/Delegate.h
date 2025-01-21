#ifndef DELEGATE_H
#define DELEGATE_H

#include <QAbstractItemDelegate>

namespace{
enum ItemGroup {
    Name,
    ModifyTime,
    Type,
    Size
};
}

class Delegate : public QAbstractItemDelegate {
public:
    explicit Delegate(QObject* parent = nullptr);

    // 绘制界面
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    // 编辑
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

    bool helpEvent(QHelpEvent* event, QAbstractItemView* view, const QStyleOptionViewItem& option, const QModelIndex& index) override;

    bool itemGroupExist(ItemGroup item_group) const;
    // 更新对应项的布局
    void updateElementRect(const QRect& rect, const QModelIndex& index);

private:
    QSize m_item_size = QSize(1400, 70);
    int m_margin = 5;
    int m_doc_margin = 10;
    QColor m_hover_color = QColor(229, 243, 255, 100);          // 鼠标悬浮时的背景色
    QColor m_selected_color = QColor(204, 232, 255, 150);       // 选中项目的背景色
    QRect m_fill_rect;
    QHash<ItemGroup, int> m_group_widths;                       // 各个分组的比例尺寸，目前暂定 名称 修改时间 类型 大小
    QRect m_doc_rect;
    QRect m_checkbox_rect;
    QRect m_icon_rect;
    QRect m_name_rect;
    QRect m_edit_rect;
    QRect m_modify_time_rect;
    QRect m_type_rect;
    QRect m_size_rect;

    QPoint m_press_pos;

};

#endif // DELEGATE_H
