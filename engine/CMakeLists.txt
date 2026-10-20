cmake_minimum_required(VERSION 3.20)

project(ShatranjOneEngine
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Main chess engine executable
add_executable(shatranj-one
    src/main.cpp
    src/position.cpp
)

# Enable useful compiler warnings
if(MSVC)
    target_compile_options(shatranj-one PRIVATE /W4)
else()
    target_compile_options(shatranj-one PRIVATE
        -Wall -Wextra -Wpedantic
    )
endif()

# Download and configure GoogleTest
include(FetchContent)


FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)


FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

add_executable(engine_tests
    tests/engine_test.cpp
    tests/position_test.cpp
)

target_link_libraries(engine_tests
    PRIVATE GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(engine_tests)