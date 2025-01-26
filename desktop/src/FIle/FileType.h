#ifndef FILETYPE_H
#define FILETYPE_H

#include <QString>

enum FileType {
    unknow = 0,
    dir = 1,
    doc = 2,
    image = 3
};

inline FileType intToFileType(int type) {
    switch (type) {
    case 1: return FileType::dir;
    case 2: return FileType::doc;
    case 3: return FileType::image;
    default: return FileType::unknow;
    };
};

inline int FileTypeToInt(FileType type) {
    if (type == FileType::dir) {
        return 1;
    } else if (type == FileType::doc) {
        return 2;
    } else if (type == FileType::image) {
        return 3;
    }
    return 0;
};

inline QString fileTypeIntToString(int _type) {
    FileType type = intToFileType(_type);
    if (type == FileType::dir) {
        return QString(u8"文件夹");
    } else if (type == FileType::doc) {
        return QString(u8"文档");
    } else if (type == FileType::image) {
        return QString(u8"图片");
    }
    return QString(u8"未知");
}

#endif // FILETYPE_H
