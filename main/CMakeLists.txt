cmake_minimum_required(VERSION 3.10)
set(CMAKE_MIN_REQ_VERSION "3.10")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("MPS_Project")

add_subdirectory(tests)

# option(BUILD_TESTS "Build tests also for ${PROJECT_NAME}" OFF)

include_directories(tests/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -std=c++17")

file(GLOB PROJECT_SOURCES parser/*.cpp inputData/*.cpp node/*.cpp operation/*.cpp randomTree/*.cpp solution/*.cpp)
file(GLOB PROJECT_HEADERS parser/*.h inputData/*.h node/*.h operation/*.h randomTree/*.h)

add_executable(
	${PROJECT_NAME}
	${PROJECT_SOURCES}
	${PROJECT_HEADERS}
)

target_link_libraries(${PROJECT_NAME} Tests)