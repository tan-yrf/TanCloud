find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

qt_add_library(Config STATIC
    NetConfig.h
    UserConfig.h
    ApiPath.h
    NetConfig.cpp
    ../../resource/icon/icon.qrc
    UserConfig.cpp
)

target_link_libraries(Config PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_include_directories(Config PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
