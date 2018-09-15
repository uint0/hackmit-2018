cmake_minimum_required(VERSION 3.9)
project(cppbe)

set(CMAKE_CXX_STANDARD 11)

include_directories(/home/admin/.local/lib/freenect2/include)
link_directories(/home/admin/.local/lib/freenect2/lib)

add_executable(cppbe main.cpp)
target_link_libraries(cppbe /home/admin/.local/lib/freenect2/lib/libfreenect2.so)
