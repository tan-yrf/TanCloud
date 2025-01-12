find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_add_library(Login STATIC
   
)

target_link_libraries(Login PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)