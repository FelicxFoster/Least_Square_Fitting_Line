cmake_minimum_required(VERSION 2.8)
project(Least_Square_Fitting_Line)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# find_package(Eigen3 REQUIRED)
find_package(PCL REQUIRED)
find_package(Ceres REQUIRED)
find_package(OpenCV REQUIRED)

# include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include 
    ${PCL_INCLUDE_DIRS} 
    ${CERES_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    # ${EIGEN3_INCLUDE_DIRS}
  )

link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(fit_straight_line src/fit_straight_line.cpp)
target_link_libraries(fit_straight_line ${PCL_LIBRARIES} ${CERES_LIBRARIES} ${OpenCV_LIBS})

add_executable(ls_test src/ls_test.cpp)
target_link_libraries(ls_test ${PCL_LIBRARIES} ${OpenCV_LIBS})
