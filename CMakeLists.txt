# 指定CMake最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(MyProject)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加可执行文件
add_executable(${PROJECT_NAME} main.cpp)

# 包含头文件目录
# include_directories(src)