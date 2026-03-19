cmake_minimum_required(VERSION 3.16)
project(IndoorHumiditySystem_DEVS CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)

add_executable(main src/main.cpp)

target_include_directories(main PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/cadmium/include
    ${CMAKE_SOURCE_DIR}/external/cadmium/json/single_include
    ${Boost_INCLUDE_DIRS}
)