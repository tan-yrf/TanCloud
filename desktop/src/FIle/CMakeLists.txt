find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_add_library(File STATIC
    ../../resource/icon/icon.qrc
)

target_link_libraries(File PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(File PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

