cmake_minimum_required(VERSION 3.16.3)
project(OpenCV_Project)

# 查找 OpenCV 包
find_package(OpenCV REQUIRED)

# 包含 OpenCV 头文件
include_directories(${OpenCV_INCLUDE_DIRS})

# 设置源文件
set(SOURCES src/main.cpp)

# 创建可执行文件，名称为 OpenCV_Project
add_executable(OpenCV_Project ${SOURCES})

# 链接 OpenCV 库
target_link_libraries(OpenCV_Project ${OpenCV_LIBS})
