cmake_minimum_required(VERSION 3.10)
set(CMAKE_MIN_REQ_VERSION "3.10")

project("MPS_Project")

add_subdirectory(tests)

# option(BUILD_TESTS "Build tests also for ${PROJECT_NAME}" OFF)

include_directories(tests/)

file(GLOB PROJECT_SOURCES parser/*.cpp)
file(GLOB PROJECT_HEADERS parser/*.h)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MTd")

add_executable(
	${PROJECT_NAME}
	${PROJECT_SOURCES}
	${PROJECT_HEADERS}
)

target_link_libraries(${PROJECT_NAME} Tests)