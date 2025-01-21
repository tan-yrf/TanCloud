#ifndef ITEMROLE_H
#define ITEMROLE_H

enum ItemRole {
    Unknow = -1,
    CheckState,
    Path,
    Icon,
    Name,
    Size,
    ModifyTime,
    Type,
    CreateTime,

    EditRole
};

inline int roleToInt(ItemRole role) {
    switch (role) {
    case ItemRole::CheckState: return 1;
    case ItemRole::Path: return 2;
    case ItemRole::Icon: return 3;
    case ItemRole::Name: return 4;
    case ItemRole::Size: return 5;
    case ItemRole::ModifyTime: return 6;
    case ItemRole::Type: return 7;
    case ItemRole::CreateTime: return 8;
    case ItemRole::EditRole: return 9;
    default: return -1;  // 默认返回 -1 表示未知角色
    }
}
#endif // ITEMROLE_H
