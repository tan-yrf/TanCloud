#ifndef ITEM_H
#define ITEM_H

#include <QHash>
#include <QVariant>

enum ItemRole {
    Path = 0,
    Name = 1,
    CreateTime = 2,
    ModifyTime = 3,
    Type = 4,
    Size = 5,

    CheckState = 100,
    Icon = 101
};

enum FileType {
    Unknow = 0,
    Dir = 1,
    Doc = 2,
    Image = 3
};
inline FileType intToFileType(int type) {
    switch (type) {
    case 1: return FileType::Dir;
    case 2: return FileType::Doc;
    case 3: return FileType::Image;
    default: return FileType::Unknow;
    };
};

inline int FileTypeToInt(FileType type) {
    if (type == FileType::Dir) {
        return 1;
    } else if (type == FileType::Doc) {
        return 2;
    } else if (type == FileType::Image) {
        return 3;
    }
    return 0;
};

inline QString fileTypeIntToString(int _type) {
    FileType type = intToFileType(_type);
    if (type == FileType::Dir) {
        return QString(u8"文件夹");
    } else if (type == FileType::Doc) {
        return QString(u8"文档");
    } else if (type == FileType::Image) {
        return QString(u8"图片");
    }
    return QString(u8"未知");
}

class Item
{
public:
    explicit Item();

    QVariant data(int role) const;
    bool setData(int role, const QVariant& value);
private:
    QHash<int, QVariant> m_data;
};

#endif // ITEM_H
