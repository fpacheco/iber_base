cmake_minimum_required(VERSION 3.1)
project(interpolate)

set(INT_SRCS main.cpp bilineal.cpp)

set(INT_HEADERS bilineal.hpp)

FILE(GLOB_RECURSE LibFiles "*.hpp")

# GDAL
FIND_PACKAGE(GDAL REQUIRED)
# BOOST PROGRAM OPTIONS
FIND_PACKAGE(Boost REQUIRED COMPONENTS system filesystem program_options)

include_directories(${GDAL_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})


add_executable(${PROJECT_NAME} ${INT_SRCS})

target_link_libraries(${PROJECT_NAME} ${GDAL_LIBRARIES} ${Boost_LIBRARIES})
