cmake_minimum_required(VERSION 3.8)


project(jianchan VERSION 0.0.1 LANGUAGES CXX)

include_directories(src)

file(GLOB src_files "src/*.cpp")
file(GLOB test_files "test_code/*.cpp")

message(STATUS ${src_files})
add_executable(jianchan ${src_files} ${test_files})