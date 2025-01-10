# Form/SideButton/CMakeLists.txt

# 查找 Qt 的 Widgets 模块
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# 设置源文件
set(SIDEBUTTON_SOURCES
    SideButton.h
    SideButton.cpp
)

# 添加 SideButton 静态库
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_library(SideButton STATIC
        ${SIDEBUTTON_SOURCES}
    )
else()
    add_library(SideButton STATIC
        ${SIDEBUTTON_SOURCES}
    )
endif()

# 连接 QtWidgets
target_link_libraries(SideButton PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
