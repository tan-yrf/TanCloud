#include <QPainter>
#include <QStyleOptionViewItem>
#include <QGridLayout>

#include "FileListView.h"
#include "ListItem.h"

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

    // 根据模型和类型重新添加项
    if (m_model == nullptr)
        return;

    for (int i = 0; i < m_model->count(); i++) {
        if (m_pattern == ViewPattern::List) {
            ListItem* item = new ListItem(this, m_model->at(i));
            m_layout.addWidget(item);
        }
    }
}
