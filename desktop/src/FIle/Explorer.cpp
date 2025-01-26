#include <QJsonObject>
#include <QJsonArray>
#include <QFileInfo>

#include "ListItem.h"
#include "ImageItem.h"
#include "Explorer.h"
#include "ui_Explorer.h"
#include "Exception.h"
#include "ApiPath.h"
#include "UserConfig.h"
#include "Request.h"


Explorer::Explorer(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::Explorer)
{
    ui->setupUi(this);
}

Explorer::~Explorer()
{
    delete ui;
}

void Explorer::setListPattern() {
    if(m_pattern == Pattern::List)
        return;
    m_pattern = Pattern::List;
    update();
}

void Explorer::setImagePattern() {
    if (m_pattern == Pattern::Image)
        return;
    m_pattern = Pattern::Image;
    update();
}

void Explorer::check(QPointF position)
{

}

void Explorer::refresh() {
    cd(m_current_path);
}



void Explorer::update() {
    QLayoutItem* item;
    while((item = ui->content->layout()->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // 根据模型和类型重新添加项
    QGridLayout* m_layout = static_cast<QGridLayout*>(ui->content->layout());
    m_layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    if (m_pattern == Pattern::List) {
        int row = 0;
        for (int i = 0; i < m_model.count(); i++) {
            ListItem* item = new ListItem(this, &m_model, i);
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
            ImageItem* item = new ImageItem(this, m_model, i);
            m_layout->addWidget(item, row, col);
            col++;
            if (col >= colums) {    // 下一行
                col = 0;
                row++;
            }
        }
    }
}

void Explorer::cd(const QString &path) {
    try {
        Request request(MethodType::post_method, ContentType::json, ApiPath::c_get_dir_info);
        request.m_head.insert("Authorization", QString("Bearer ").append(UserConfig::token));
        request.m_form_body.insert("path", path);
        Response response = request.send();

        // 获取成功，更新模型和界面
        if (response.code == 0) {
            m_model.clear();
            QJsonArray array = response.body["array"].toArray();
            QVector<Item> items;
            for(const auto& a : array) {
                QJsonObject obj = a.toObject();
                Item item;
                item.setData(ItemRole::Path, obj["path"].toString());
                item.setData(ItemRole::Name, obj["name"].toString());
                item.setData(ItemRole::CreateTime, obj["create_time"].toString());
                item.setData(ItemRole::ModifyTime, obj["last_modify_time"].toString());
                if (obj["is_dir"].toBool()) {
                    item.setData(ItemRole::Type, FileType::Dir);
                } else {
                    if (isImage(obj["name"].toString())) {
                        item.setData(ItemRole::Type, FileType::Image);
                    } else {
                        item.setData(ItemRole::Type, FileType::Doc);
                    }
                }
                item.setData(ItemRole::Size, obj["size"].toInteger());

                // 设置图标，暂时没有实现获取图片
                if (item.data(ItemRole::Type) == FileType::Dir) {
                    item.setData(ItemRole::Icon, QImage(":/FIle/folder.svg"));
                } else if (item.data(ItemRole::Type) == FileType::Doc) {
                    item.setData(ItemRole::Icon, QImage(":/FIle/file.svg"));
                } else if (item.data(ItemRole::Type) == FileType::Image) {
                    item.setData(ItemRole::Icon, QImage(":/FIle/image.svg"));
                }
                items.append(item);
            }
            m_model.appendList(items);
            refresh();
        }
    } catch(Exception e) {
        e.showMessage();
    }
}

bool Explorer::isImage(const QString &file_name) const {
    static const QSet<QString> image_extensions = {
        "jpg", "jpeg", "png", "gif", "bmp", "webp", "tiff", "svg"
    };
    QFileInfo fileInfo(file_name);
    QString suffix = fileInfo.suffix().toLower();

    // 判断后缀名是否在图片后缀名集合中
    return image_extensions.contains(suffix);
}


