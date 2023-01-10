cmake_minimum_required(VERSION 3.10)
set(CMAKE_MIN_REQ_VERSION "3.10")

set(CMAKE_CXX_STANDARD 17)
# Don't add this line if you will try_compile with boost.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("Tests")

set(BUILD_GMOCK ON)
add_subdirectory(lib/googletest/)

include_directories(
	"${PROJECT_SOURCE_DIR}/lib/googletest/googlemock/include/"
	"${PROJECT_SOURCE_DIR}/lib/googletest/googletest/include/"
	)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MTd")

file(GLOB PROJECT_SOURCES *.cpp)
file(GLOB PROJECT_HEADERS *.h)

add_library(${PROJECT_NAME} STATIC
             ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_link_libraries(${PROJECT_NAME} gtest gmock)
