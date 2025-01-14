find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_add_library(Login STATIC
    Login.h Login.cpp Login.ui
    ../../resource/icon/icon.qrc
)

target_link_libraries(Login PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Exception Config)
