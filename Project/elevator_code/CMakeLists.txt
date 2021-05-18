cmake_minimum_required(VERSION 3.5)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

project(elevator_sim LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
add_subdirectory(simulation)

add_executable(elevator_sim
    main.c
    simulation/elevator.h
    # ADD YOUR EXTRA SOURCE FILES HERE
    elevator.h
    elevator.c
    elevator_data.c
    rt_nonfinite.c
    rtGetInf.c
    rtGetNaN.c
)
target_link_libraries(elevator_sim LINK_PUBLIC Simulation m)

