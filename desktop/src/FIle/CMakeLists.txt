find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_add_library(File STATIC
    ../../resource/icon/icon.qrc
    Home.h Home.cpp Home.ui
    FileExplorer.h FileExplorer.cpp FileExplorer.ui
    ViewHeader.h ViewHeader.cpp ViewHeader.ui

    FileListModel.h FileListModel.cpp
    FileListItem.h FileListItem.cpp
    ListItem.h ListItem.cpp ListItem.ui
    ImageItem.h ImageItem.cpp ImageItem.ui
    FIleItemRole.h
    MetaItem.h MetaItem.cpp
    FileType.h
    FileListView.h FileListView.cpp FileListView.ui


)

target_link_libraries(File PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(File PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

