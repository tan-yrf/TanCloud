# 设置最低CMake版本要求
cmake_minimum_required(VERSION 3.16)

# 项目名称和版本号定义
# `LANGUAGES CXX` 表示项目使用 C++ 编程语言
project(TanCloudPc VERSION 0.1 LANGUAGES CXX)

# 启用Qt的自动UI、自动MOC（Meta-Object Compiler）和自动RCC（Qt资源文件编译器）支持
set(CMAKE_AUTOUIC ON)    # 启用自动UI文件处理
set(CMAKE_AUTOMOC ON)    # 启用自动MOC文件处理
set(CMAKE_AUTORCC ON)    # 启用自动RCC文件处理

# 设置C++的标准为C++17，并要求使用C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Qt库，要求至少包含Qt6或Qt5，并且需要Widgets模块
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

########################################################################################
# 添加引用的模块

# 添加 src/MainWindow 目录中的CMakeLists.txt文件，表示将该子目录包含到构建过程中
# 这样，MainWindow模块将成为项目的一部分
add_subdirectory(src/MainWindow)

# 添加自定义的侧边栏按钮模块
add_subdirectory(src/Form/SideButton ${CMAKE_BINARY_DIR}/Form/SideButton)

# 添加文件模块
add_subdirectory(src/File)

# 添加传输模块
add_subdirectory(src/Transfer)

# 添加分享模块
add_subdirectory(src/Share)

#########################################################################################

#########################################################################################
# 添加文件模块的头文件到MainWindow模块
target_include_directories(MainWindow PUBLIC ${CMAKE_SOURCE_DIR}/src/File)

# 将SideButton 的头文件路径包含到 MainWindow 中
target_include_directories(MainWindow PUBLIC ${CMAKE_SOURCE_DIR}/src/Form/SideButton)

# 将 传输 模块的头文件包含到MainWindow中
target_include_directories(MainWindow PUBLIC ${CMAKE_SOURCE_DIR}/src/Transfer)

# 将 分享 模块的头文件包含到MainWindow中
target_include_directories(MainWindow PUBLIC ${CMAKE_SOURCE_DIR}/src/Share)
#########################################################################################


# 设置项目的源文件
# 这里包含了 main.cpp 文件，注意路径使用相对路径
set(PROJECT_SOURCES
    src/main.cpp
)

# 根据Qt的版本进行不同的处理
# 如果Qt版本为6或更高，使用qt_add_executable来生成可执行文件
# 如果是Qt5或更低版本，使用add_executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TanCloudPc
        MANUAL_FINALIZATION  # 手动结束finalization，后续需要执行qt_finalize_executable
        ${PROJECT_SOURCES}   # 将项目源文件加入
        resource/icon/icon.qrc
    )
else()
    add_executable(TanCloudPc
        ${PROJECT_SOURCES}   # 将项目源文件加入
    )
endif()

# 连接 MainWindow 模块
# 将 MainWindow 库链接到主可执行文件TanCloudPc
target_link_libraries(TanCloudPc PRIVATE MainWindow)

# 链接Qt的Widgets库
# 这一步将QtWidgets库连接到主可执行文件
target_link_libraries(TanCloudPc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# 针对iOS和Mac的配置
# Qt 6.1及以上版本会自动设置MACOSX_BUNDLE_GUI_IDENTIFIER
# 但如果版本低于6.1，可以手动设置Bundle Identifier
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TanCloudPc)
endif()

# 设置目标的相关属性
set_target_properties(TanCloudPc PROPERTIES
    ${BUNDLE_ID_OPTION}                        # 设置Bundle标识符
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION} # 设置应用程序的版本
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}  # 设置短版本号
    MACOSX_BUNDLE TRUE                         # 设置为macOS应用包
    WIN32_EXECUTABLE TRUE                      # 设置为Windows可执行文件
)

# 包含GNU标准安装目录设置，确保目标安装路径合理
include(GNUInstallDirs)

# 安装TanCloudPc可执行文件和相关库
install(TARGETS TanCloudPc
    BUNDLE DESTINATION .              # 安装到当前目录（macOS和iOS应用包）
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}  # 安装库文件
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}  # 安装可执行文件
)

# 如果是Qt6，调用qt_finalize_executable来完成最终的Qt可执行文件设置
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TanCloudPc)
endif()
