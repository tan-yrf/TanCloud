find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_add_library(SideBar STATIC
    SideBar.h SideBar.cpp SideBar.ui
    ../../resource/icon/icon.qrc
)

target_link_libraries(SideBar PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Config)
target_include_directories(SideBar PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

