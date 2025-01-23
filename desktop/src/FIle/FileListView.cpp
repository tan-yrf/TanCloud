#include <QPainter>
#include <QStyleOptionViewItem>
#include <QGridLayout>

#include "FileListView.h"
#include "ListItem.h"
#include "ImageItem.h"

FileListView::FileListView(QWidget *parent)
    : QWidget(parent),
    m_content_widget(this),
    m_layout(&m_content_widget){

    m_content_widget.setLayout(&m_layout);

    m_area.setWidget(&m_content_widget);
    m_area.setWidgetResizable(true);

    QGridLayout* main_layout = new QGridLayout(this);
    main_layout->addWidget(&m_area, 0, 0);
    this->setLayout(main_layout);
}

void FileListView::setModel(FileListModel *model) {
    if (m_model && m_model == model)
        return;

    if (m_model) {
        disconnect(m_model, &FileListModel::dataChanged, this, &FileListView::update);
    }

    m_model = model;
    if (m_model) {
        connect(m_model, &FileListModel::dataChanged, this, &FileListView::update);
    }

    update();
}

void FileListView::setPattern(ViewPattern pattern) {
    if (m_pattern == pattern)
        return;
    m_pattern = pattern;
    update();
}

void FileListView::update() {
    // 清空原有项
    QLayoutItem* item;
    while((item = m_layout.takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    if (m_model == nullptr)
        return;

    // 根据模型和类型重新添加项
    if (m_pattern == ViewPattern::List) {
        int row = 0;
        for (int i = 0; i < m_model->count(); i++) {
            ListItem* item = new ListItem(this, m_model->at(i));
            m_layout.addWidget(item, row, 0);
            row++;
        }
    }

    if (m_pattern == ViewPattern::Image) {
        int space = 100;
        m_layout.setSpacing(space);
        int contain_width = m_area.viewport()->width();
        int item_width = 150;   // 每一项的宽度,后续如果有需要再改成动态获取

        // 计算能够容纳多少列
        int colums = contain_width / (item_width + space);
        if (colums == 0)
            colums = 1;

        int row = 0;
        int col = 0;

        for (int i = 0; i < m_model->count(); i++) {
            ImageItem* item = new ImageItem(this, m_model->at(i));
            m_layout.addWidget(item, row, col);
            col++;
            if (col >= colums) {    // 下一行
                col = 0;
                row++;
            }
        }
    }
}
