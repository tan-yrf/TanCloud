find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_add_library(Network STATIC
    Response.h Response.cpp
    Request.h Request.cpp

)

target_link_libraries(Network PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${Boost_LIBRARIES} OpenSSL::Crypto OpenSSL::SSL Exception Config)
target_include_directories(Network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
