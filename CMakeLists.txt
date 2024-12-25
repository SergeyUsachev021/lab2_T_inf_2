cmake_minimum_required(VERSION 3.10)
project(MyExecutable)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


set(SOURCE_FILES
    main.cpp
    shannonFano.cpp
    huffmanCode.cpp
    task.cpp
)


add_executable(MyExecutable ${SOURCE_FILES})