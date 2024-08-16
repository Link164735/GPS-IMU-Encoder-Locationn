cmake_minimum_required(VERSION 3.10)  

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

project(ExtendedKalmanFilter)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../include)

set(SOURCES
    main.cpp
    ekf.cpp
    fusion.cpp
    geo_ned.cpp
    run_fusion.cpp
    utils.cpp
)

add_executable(ExtendedKalmanFilter ${SOURCES} ${HEADERS})

target_link_libraries(ExtendedKalmanFilter PRIVATE Eigen3::Eigen)

# target_link_libraries(ExtendedKalmanFilter PRIVATE <库名>)

# Enable debugging symbols
set(CMAKE_BUILD_TYPE Debug)

# Optionally, set compiler flags for debugging
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")