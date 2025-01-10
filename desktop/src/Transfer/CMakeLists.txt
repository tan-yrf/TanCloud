# 查找 Qt 的 widgets 模块
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 定义 Transfer 静态库
qt_add_library(Transfer STATIC
    ../../resource/icon/icon.qrc
    Transfer.h Transfer.cpp Transfer.ui
)

# 链接 Qt 的 widgets 模块
target_link_libraries(Transfer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
