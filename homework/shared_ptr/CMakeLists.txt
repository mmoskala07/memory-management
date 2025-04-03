cmake_minimum_required(VERSION 3.11.0)
project(shared_ptr)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${PROJECT_NAME}_tests ${PROJECT_NAME}_tests.cpp)

target_link_libraries(${PROJECT_NAME}_tests gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)
