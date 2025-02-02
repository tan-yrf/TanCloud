#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFileInfo>
#include <QLayoutItem>

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
    , ui(new Ui::Explorer) {
    ui->setupUi(this);

    connect(&m_model, &Model::checkedChanged, this, &Explorer::onCheckedChanged);
}

Explorer::~Explorer()
{
    delete ui;
}

void Explorer::setListPattern() {
    if(m_pattern == Pattern::List)
        return;
    m_pattern = Pattern::List;
    m_model.resetAllCheckBoxState();
    update();
}

void Explorer::setImagePattern() {
    if (m_pattern == Pattern::Image)
        return;
    m_pattern = Pattern::Image;
    m_model.resetAllCheckBoxState();
    update();
}

void Explorer::checkAll(bool state) {
    m_model.checkAll(state);

    for (int i = 0; i < m_layout->count(); i++) {
        QLayoutItem* item = m_layout->itemAt(i);
        if (item && item->widget()) {
            QWidget* widget = item->widget();
            if (auto list_item = qobject_cast<ListItem*>(widget)) {
                list_item->setChecked(state);
            } else if (auto image_item = qobject_cast<ImageItem*>(widget)) {
                image_item->setChecked(state);
            }
        }
    }
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
    m_layout = static_cast<QGridLayout*>(ui->content->layout());
    m_layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    if (m_pattern == Pattern::List) {
        m_layout->setSpacing(5);
        m_layout->setColumnMinimumWidth(0, 1);
        m_layout->setColumnStretch(0, 1);

        int row = 0;
        for (int i = 0; i < m_model.count(); i++) {
            ListItem* item = new ListItem(this, &m_model, i);
            m_layout->addWidget(item, row, 0, Qt::AlignTop); // 显式设置对齐
            row++;
        }

        // 添加弹簧到最后一行的下一行，并指定垂直拉伸
        m_layout->addItem(
            new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding),
            row, 0, 1, 1, Qt::AlignTop
            );
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

        for (int i = 0; i < m_model.count(); i++) {
            ImageItem* item = new ImageItem(this, &m_model, i);
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
            m_current_path = path;
            update();
            emit pathChanged(m_current_path);
            //qDebug() <<u8"数量" << m_model.count();
            if (m_model.count() == 0) {
                emit countChanged(0, 0);
            }
        }
    } catch(Exception e) {
        e.showMessage();
    }
}

void Explorer::back() {
    QFileInfo file_info(m_current_path);
    m_current_path = file_info.path();
    cd(m_current_path);
}

bool Explorer::createFolder(QString &message, const QString& folder_name) {
    try {
        Request request(MethodType::post_method, ContentType::json, ApiPath::c_create_folder);
        request.m_head.insert("Authorization", QString("Bearer ").append(UserConfig::token));
        request.m_form_body.insert("path", m_current_path);
        request.m_form_body.insert("name", folder_name);
        Response response = request.send();

        message = response.message;
        if (response.code == 0) {
            refresh();
            return true;
        }
    } catch(Exception e) {
        e.showMessage();
    }
    return false;
}

bool Explorer::deleteSelected(QString &message) {
    try {
        Request request(MethodType::post_method, ContentType::json, ApiPath::c_delete_complete);
        request.m_head.insert("Authorization", QString("Bearer ").append(UserConfig::token));
        QVector<Item> items = m_model.getSelectedItems();
        QJsonArray paths;
        for (const auto& item : items) {
            paths.append(item.data(ItemRole::Path).toString());
        }
        QJsonObject obj;
        obj["paths"] = paths;
        QJsonDocument doc(obj);
        QString body = doc.toJson();
        request.m_json_body = body;
        Response response = request.send();

        message = response.message;
        if (response.code == 0) {
            refresh();
            return true;
        }
    } catch (Exception e) {
        e.showMessage();
    }
    return false;
}

void Explorer::resizeEvent(QResizeEvent *event) {
    update();
}

void Explorer::mousePressEvent(QMouseEvent *event) {
    QPoint pos = ui->view->mapFromParent(event->pos());
    if (ui->view->rect().contains(pos) == false)
        return QWidget::mousePressEvent(event);

    QPointF global_pos = event->globalPosition();
    event->accept();
    check(global_pos);

    if (event->button() == Qt::RightButton) {
        //m_menu.showAtPosition(global_pos);
        return QWidget::mousePressEvent(event);
    }
}

void Explorer::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QPoint pos = ui->view->mapFromParent(event->pos());
        if (ui->view->rect().contains(pos) == false)
            return QWidget::mousePressEvent(event);

        QPointF global_pos = event->globalPosition();
        entery(global_pos);
        event->accept();
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

void Explorer::check(QPointF position) {
    QPoint pos = position.toPoint();
    QPoint local_pos = ui->content->mapFromGlobal(pos);

    QWidget* child = ui->content->childAt(local_pos);
    if (child == nullptr)
        return;

    // 向上查找父控件，直到找到 ListItem 或 ImageItem
    QWidget* current = child;
    while (current) {
        ListItem* list_item = qobject_cast<ListItem*>(current);
        ImageItem* image_item = qobject_cast<ImageItem*>(current);

        if(list_item) {
            list_item->setChecked(true);
            break;
        } else if(image_item) {
            image_item->setChecked(true);
            break;
        }
        current = current->parentWidget();
    }
}

void Explorer::entery(QPointF position) {
    QPoint pos = position.toPoint();
    QPoint local_pos = ui->content->mapFromGlobal(pos);

    QWidget* child = ui->content->childAt(local_pos);
    if (child == nullptr)
        return;

    // 向上查找父控件，直到找到 ListItem 或 ImageItem
    QWidget* current = child;
    while (current) {
        ListItem* list_item = qobject_cast<ListItem*>(current);
        ImageItem* image_item = qobject_cast<ImageItem*>(current);

        if (list_item || image_item) {
            int index = -1;
            if(list_item) {
                index = list_item->index();
            } else if(image_item) {
                index = image_item->index();
            }
            if (m_model.indexIsValid(index)) {
                Item item = m_model.at(index);
                if (item.data(ItemRole::Type) == FileType::Dir) {
                    QString path = item.data(ItemRole::Path).toString();
                    cd(path);
                }
            }
            break;
        }

        current = current->parentWidget();
    }
}

void Explorer::onCheckedChanged() {
    int selected = m_model.checkedCount();
    int sum = m_model.count();
    emit countChanged(selected, sum);
}

