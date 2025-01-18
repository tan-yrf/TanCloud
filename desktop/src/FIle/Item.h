#ifndef ITEM_H
#define ITEM_H

#include <QString>
enum FileType {
    dir,
    doc,
    image,
    unknow
};

class Item {
public:
    Item();

    QString path() const;
    QString name() const;
    qint64 size() const;
    bool selecteState() const;
    qint64 createTime() const;
    qint64 lastModifyTime() const;
    FileType type() const;

    void setSelectState(bool state);

private:
    QString m_path;
    QString m_name;
    qint64 m_size = 0;      // 单位是字节，显示时进行换算
    bool m_selected = false;
    qint64 m_create_time = 0;
    qint64 m_last_modify_time = 0;
    FileType m_type = FileType::unknow;
};

#endif // ITEM_H
