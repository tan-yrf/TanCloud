find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_add_library(MainWindow STATIC
    ../../resource/icon/icon.qrc
    MainWindow.h MainWindow.cpp MainWindow.ui
)

target_link_libraries(MainWindow PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Exception Config Network SideBar File Transfer Share)
