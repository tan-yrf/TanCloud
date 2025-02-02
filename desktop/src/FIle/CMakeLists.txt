find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_add_library(File STATIC
    ../../resource/icon/icon.qrc
    Home.h Home.cpp Home.ui
    Explorer.h Explorer.cpp Explorer.ui
    Item.h Item.cpp
    ImageItem.h ImageItem.cpp ImageItem.ui
    ListItem.h ListItem.cpp ListItem.ui
    Model.h Model.cpp
    Menu.h Menu.cpp Menu.ui
)

target_link_libraries(File PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Exception Config Network)
target_include_directories(File PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

