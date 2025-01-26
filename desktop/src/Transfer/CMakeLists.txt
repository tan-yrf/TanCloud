find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_add_library(Transfer STATIC
    ../../resource/icon/icon.qrc
    Transfer.h Transfer.cpp Transfer.ui
)

target_link_libraries(Transfer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(Transfer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

