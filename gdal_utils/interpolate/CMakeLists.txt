cmake_minimum_required(VERSION 3.1)
project(interpolate)

# GDAL
FIND_PACKAGE(GDAL REQUIRED)
# BOOST PROGRAM OPTIONS
FIND_PACKAGE(Boost REQUIRED COMPONENTS system filesystem program_options)

IF(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
ENDIF()

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME} ${GDAL_LIBRARIES} ${Boost_LIBRARIES})
