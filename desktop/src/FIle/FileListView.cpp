#include "FileListView.h"
#include "ui_FileListView.h"
#include "ImageItem.h"
#include "ListItem.h"

FileListView::FileListView(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::FileListView)
{
    ui->setupUi(this);
}

FileListView::~FileListView() {
    delete ui;
    if (m_model) {
        delete m_model;
    }
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

void FileListView::setListPattern() {
    if (m_pattern == Pattern::List)
        return;
    m_pattern = Pattern::List;
    update();
}

void FileListView::setImagePattern() {
    if (m_pattern == Pattern::Image)
        return;
    m_pattern = Pattern::Image;
    update();
}

void FileListView::update() {
    QLayoutItem* item;
    while((item = ui->content->layout()->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    if (m_model == nullptr)
        return;

    // 根据模型和类型重新添加项
    QGridLayout* m_layout = static_cast<QGridLayout*>(ui->content->layout());
    if (m_pattern == Pattern::List) {
        int row = 0;
        for (int i = 0; i < m_model->count(); i++) {
            ListItem* item = new ListItem(this, m_model->at(i));
            m_layout->addWidget(item, row, 0);
            row++;
        }
    }

    if (m_pattern == Pattern::Image) {
        int space = 50;
        m_layout->setSpacing(space);
        int contain_width = ui->content->width();
        int item_width = 150;   // 每一项的宽度,后续如果有需要再改成动态获取

        // 计算能够容纳多少列
        int colums = contain_width / (item_width + space);
        if (colums == 0)
            colums = 1;

        int row = 0;
        int col = 0;

        for (int i = 0; i < m_model->count(); i++) {
            ImageItem* item = new ImageItem(this, m_model->at(i));
            m_layout->addWidget(item, row, col);
            col++;
            if (col >= colums) {    // 下一行
                col = 0;
                row++;
            }
        }
    }
}


