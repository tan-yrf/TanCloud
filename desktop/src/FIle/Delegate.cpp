#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QToolTip>
#include <QHelpEvent>

#include "Delegate.h"
#include "ItemRole.h"

Delegate::Delegate(QObject *parent) {}

void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {

}

QSize Delegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return m_item_size;
}

QWidget *Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QLineEdit* line_edit = new QLineEdit(parent);

    // todo 编辑事件
    return line_edit;
}

void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    if (QLineEdit* line_edit = dynamic_cast<QLineEdit*>(editor)) {
        line_edit->setText(index.data(ItemRole::EditRole).toString());
    }
}

void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    auto line_edit = dynamic_cast<QLineEdit*>(model);
    if (line_edit) {
        auto sort_model = dynamic_cast<QSortFilterProxyModel*>(model);
        auto name_str = line_edit->text();
        name_str.remove(QRegularExpression("\\s+$")); // 删除末尾所有空白字符
        if (name_str.isEmpty() == false && name_str != index.data(ItemRole::Name).toString()){
            // todo 重命名
        }

    }

}

void Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    const_cast<Delegate*>(this)->updateElementRect(option.rect, index);
    auto edit_rect = m_name_rect.adjusted(0, 20, 0, -20);
    editor->setGeometry(edit_rect);
}

bool Delegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    return false;

}

bool Delegate::helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index) {
    this->updateElementRect(option.rect, index);
    auto cur_pos = event->pos();
    // 文档名触发tip
    if (m_doc_rect.contains(cur_pos))
    {
        // todo 展示文档详细信息
        //QToolTip::showText(event->globalPos(), index.data(FileData::ToolTipRole).toString(), view->viewport(), m_doc_rect);
    }
    return false;
}

bool Delegate::itemGroupExist(ItemGroup item_group) const {
    return m_group_widths.contains(item_group);
}

void Delegate::updateElementRect(const QRect &rect, const QModelIndex &index) {
    m_fill_rect = rect.adjusted(m_margin, m_margin, -m_margin, -m_margin);
    int max_height = m_fill_rect.height();
    auto fill_top_left_pos = m_fill_rect.topLeft();
    int current_width = 0;          // 当前使用的宽度

    int doc_name_width = m_group_widths[ItemGroup::Name];
    QPoint doc_top_let_pos = fill_top_left_pos;
    doc_top_let_pos.setX(fill_top_left_pos.x() + current_width);
    m_doc_rect = QRect(doc_top_let_pos, QSize(doc_name_width, max_height));
    current_width += doc_name_width;
    int doc_margin = m_doc_margin;

    int check_width = max_height / 3;   // 勾选框是正方形,宽高一样
    QPoint check_top_left_pos;
    check_top_left_pos.setX(fill_top_left_pos.x() + doc_margin);
    check_top_left_pos.setY(fill_top_left_pos.y() + check_width);
    m_checkbox_rect = QRect(check_top_left_pos, QSize(check_width, check_width));

    int icon_width = max_height / 2 + 30;
    QPoint icon_top_left_pos;
    icon_top_left_pos.setX(check_top_left_pos.x() +  check_width + doc_margin);
    icon_top_left_pos.setY(fill_top_left_pos.y() + (max_height - icon_width) / 2);
    m_icon_rect = QRect(icon_top_left_pos, QSize(icon_width, icon_width));

    int name_height = icon_width;
    int name_width = doc_name_width - check_width - icon_width - doc_margin * 3;
    QPoint name_top_left_pos;
    name_top_left_pos.setX(icon_top_left_pos.x() +  icon_width + doc_margin);
    name_top_left_pos.setY(icon_top_left_pos.y());
    m_name_rect = QRect(name_top_left_pos, QSize(name_width, name_height));
    name_top_left_pos.setY(fill_top_left_pos.y());
    m_edit_rect = QRect(name_top_left_pos, QSize(name_width, max_height));

    // 最后修改时间
    if (itemGroupExist(ItemGroup::ModifyTime)) {
        int modify_time_width = m_group_widths[ItemGroup::ModifyTime];
        QPoint time_top_left_pos = fill_top_left_pos;
        time_top_left_pos.setX(fill_top_left_pos.x() + current_width);
        current_width += modify_time_width;
        m_modify_time_rect = QRect(time_top_left_pos, QSize(modify_time_width, max_height));
    }

    // 文档类型
    if (itemGroupExist(ItemGroup::Type)) {
        int type_width = m_group_widths[ItemGroup::Type];
        QPoint type_top_left_pos = fill_top_left_pos;
        type_top_left_pos.setX(fill_top_left_pos.x() + current_width);
        current_width += type_width;
        m_type_rect = QRect(type_top_left_pos, QSize(type_width, max_height));
    }

    // 文件大小
    if (itemGroupExist(ItemGroup::Size)) {
        int size_width = m_group_widths[ItemGroup::Size];
        QPoint size_top_left_pos = fill_top_left_pos;
        size_top_left_pos.setX(fill_top_left_pos.x() + current_width);
        current_width += size_width;
        m_size_rect = QRect(size_top_left_pos, QSize(size_width, max_height));
    }
}


