find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

qt_add_library(Network
    Response.h Response.cpp
    Request.h Request.cpp

)

target_link_libraries(Network PRIVATE Qt${QT_VERSION_MAJOR}::Core ${Boost_LIBRARIES} OpenSSL::Crypto OpenSSL::SSL Config)
target_include_directories(Network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
