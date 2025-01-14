cmake_minimum_required(VERSION 3.16)
project(TanCloud VERSION 0.1 LANGUAGES CXX)

# 启用Qt的自动UI、自动MOC（Meta-Object Compiler）和自动RCC（Qt资源文件编译器）支持
set(CMAKE_AUTOUIC ON)    
set(CMAKE_AUTOMOC ON)    
set(CMAKE_AUTORCC ON)    

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Qt库，要求至少包含Qt6或Qt5，并且需要Widgets模块
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 查找 OpenSSL 库
find_package(OpenSSL REQUIRED)

# 打印 OpenSSL 的路径
message(STATUS "OpenSSL_INCLUDE_DIR: ${OPENSSL_INCLUDE_DIR}")
message(STATUS "OpenSSL_LIBRARIES: ${OPENSSL_LIBRARIES}")

# 查找 Boost 库，指定需要的模块
set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/3rdparty/boost_1_87_0")  # 设置 Boost 的根路径
set(Boost_USE_STATIC_LIBS ON)   # 使用静态库（如果需要动态库，设置为 OFF）
set(Boost_USE_MULTITHREADED ON) # 启用多线程支持
find_package(Boost 1.87 REQUIRED COMPONENTS system)

set(PROJECT_SOURCES 
    src/main.cpp
)

qt_add_executable(
    TanCloud
    MANUAL_FINALIZATION  
    ${PROJECT_SOURCES}
    resource/icon/icon.qrc
)

# 检查并配置 Boost
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_libraries(${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Boost not found!")
endif()

target_link_libraries(TanCloud PRIVATE Qt${QT_VERSION_MAJOR}::Widgets OpenSSL::Crypto OpenSSL::SSL Login Exception)

# 针对iOS和Mac的配置
# Qt 6.1及以上版本会自动设置MACOSX_BUNDLE_GUI_IDENTIFIER
# 但如果版本低于6.1，可以手动设置Bundle Identifier
if(APPLE AND ${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TanCloud)
endif()


# 设置目标的相关属性
set_target_properties(TanCloud PROPERTIES
    ${BUNDLE_ID_OPTION}                        # 设置Bundle标识符
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION} # 设置应用程序的版本
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}  # 设置短版本号
    MACOSX_BUNDLE TRUE                         # 设置为macOS应用包
    WIN32_EXECUTABLE TRUE                      # 设置为Windows可执行文件
)

###############################################添加引用模块################################
# 添加异常模块
add_subdirectory(src/Exception)

# 添加配置模块
add_subdirectory(src/Config)

# 添加网络模块
add_subdirectory(src/Network)

# 添加登录模块
add_subdirectory(src/Login)

###############################################结束添加引用################################

# 包含GNU标准安装目录设置，确保目标安装路径合理
include(GNUInstallDirs)

# 安装TanCloud可执行文件和相关库
install(TARGETS TanCloud
    BUNDLE DESTINATION .              # 安装到当前目录（macOS和iOS应用包）
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}  # 安装库文件
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}  # 安装可执行文件
)

# 如果是Qt6，调用qt_finalize_executable来完成最终的Qt可执行文件设置
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TanCloud)
endif()
