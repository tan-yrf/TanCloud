# 查找 Qt 的 Widgets 模块
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# 设置源文件
set(MAINWINDOW_SOURCES
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
)

# 使用 qt_add_library 来创建 Qt6 的静态库（因为你使用的是 Qt6）
qt_add_library(MainWindow STATIC
    ${MAINWINDOW_SOURCES}
)

# 将 SideButton 库链接到 MainWindow
target_link_libraries(MainWindow PRIVATE SideButton)

# 链接 File 库
target_link_libraries(MainWindow PRIVATE File)

# 链接 Transfer 库
target_link_libraries(MainWindow PRIVATE Transfer)

# 链接 Share 库
target_link_libraries(MainWindow PRIVATE Share)

# 将 MainWindow 依赖于 QtWidgets
target_link_libraries(MainWindow PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# 让目标 MainWindow 的头文件对外部可见
target_include_directories(MainWindow PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
