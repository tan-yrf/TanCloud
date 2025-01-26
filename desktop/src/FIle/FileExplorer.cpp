#include <QMouseEvent>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileInfo>

#include "FileExplorer.h"
#include "ui_FileExplorer.h"
#include "FIleItemRole.h"
#include "FileType.h"

#include "Request.h"
#include "Response.h"
#include "ApiPath.h"
#include "UserConfig.h"
#include "Exception.h"

FileExplorer::FileExplorer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileExplorer)
{
    ui->setupUi(this);

    m_model.setParent(this);
    ui->list_view->setModel(&m_model);
}

FileExplorer::~FileExplorer()
{
    delete ui;
}

void FileExplorer::setListPattern() {
    ui->list_view->setListPattern();
    ui->header->setListPattern();
}

void FileExplorer::setImagePattern() {
    ui->list_view->setImagePattern();
    ui->header->setImagePattern();
}

void FileExplorer::refresh() {
    cd(m_current_path);
}

void FileExplorer::cd(const QString path) {
    try {
        Request request(MethodType::post_method, ContentType::json, ApiPath::c_get_dir_info);
        request.m_head.insert("Authorization", QString("Bearer ").append(UserConfig::token));
        request.m_form_body.insert("path", path);
        Response response = request.send();

        // 获取成功，更新模型和界面
        if (response.code == 0) {
            m_model.clear();
            QJsonArray array = response.body["array"].toArray();
            QVector<FileListItem> items;
            for(const auto& a : array) {
                QJsonObject obj = a.toObject();
                FileListItem item;
                item.setData(ItemRole::Path, obj["path"].toString());
                item.setData(ItemRole::Name, obj["name"].toString());
                item.setData(ItemRole::CreateTime, obj["create_time"].toString());
                item.setData(ItemRole::ModifyTime, obj["last_modify_time"].toString());
                if (obj["is_dir"].toBool()) {
                    item.setData(ItemRole::Type, FileType::dir);
                } else {
                    if (isImage(obj["name"].toString())) {
                        item.setData(ItemRole::Type, FileType::image);
                    } else {
                        item.setData(ItemRole::Type, FileType::doc);
                    }
                }
                item.setData(ItemRole::Size, obj["size"].toInteger());

                // 设置图标，暂时没有实现获取图片
                if (item.data(ItemRole::Type) == FileType::dir) {
                    item.setData(ItemRole::Icon, QImage(":/FIle/folder.svg"));
                } else if (item.data(ItemRole::Type) == FileType::doc) {
                    item.setData(ItemRole::Icon, QImage(":/FIle/file.svg"));
                } else if (item.data(ItemRole::Type) == FileType::image) {
                    item.setData(ItemRole::Icon, QImage(":/FIle/image.svg"));
                }
                items.append(item);
            }
            m_model.appendList(items);
            ui->list_view->refresh();
        }
    } catch(Exception e) {
        e.showMessage();
    }
}

// 只有右键，并且在view范围中的事件才会触发
void FileExplorer::mousePressEvent(QMouseEvent *event) {
    if (event->button() != Qt::RightButton)
        return QWidget::mousePressEvent(event);
    QPoint pos = ui->list_view->mapFromParent(event->pos());
    if (ui->list_view->rect().contains(pos) == false)
        return QWidget::mousePressEvent(event);

    QPointF global_pos = event->globalPosition();
    m_menu.showAtPosition(global_pos);
    event->accept();
    ui->list_view->check(global_pos);
    return QWidget::mousePressEvent(event);
}

void FileExplorer::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() != Qt::LeftButton) {
        return QWidget::mouseDoubleClickEvent(event);
    }
}

bool FileExplorer::isImage(const QString &file_name) const {
    static const QSet<QString> image_extensions = {
        "jpg", "jpeg", "png", "gif", "bmp", "webp", "tiff", "svg"
    };
    QFileInfo fileInfo(file_name);
    QString suffix = fileInfo.suffix().toLower();

    // 判断后缀名是否在图片后缀名集合中
    return image_extensions.contains(suffix);
}

