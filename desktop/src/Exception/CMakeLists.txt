find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

qt_add_library(Exception STATIC
    Exception.h Exception.cpp

)

target_link_libraries(Exception PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_include_directories(Exception PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

