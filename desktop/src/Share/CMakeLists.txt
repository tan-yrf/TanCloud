# 查找 Qt 的 widgets 模块
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_add_library(Share STATIC
    ../../resource/icon/icon.qrc
    Share.h Share.cpp Share.ui

)

target_link_libraries(Share PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
