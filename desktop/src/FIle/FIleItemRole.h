#ifndef FILEITEMROLE_H
#define FILEITEMROLE_H

// 前面是元信息，后面是于显示相关的
enum ItemRole {
    Path = 0,
    Name = 1,
    CreateTime = 2,
    ModifyTime = 3,
    Type = 4,
    Size = 5,                   // 单位是自己，显示时进行换算


    CheckBox = 100,             // 不需要勾选框则设置为false，默认需要
    Icon = 101
};
#endif // FILEITEMROLE_H
