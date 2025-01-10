# 查找 Qt 的 widgets 模块
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_add_library(File STATIC
    HomePage.h HomePage.cpp HomePage.ui
    ../../resource/icon/icon.qrc
)

# 链接 Qt 的 widgets 模块
target_link_libraries(File PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
