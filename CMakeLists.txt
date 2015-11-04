cmake_minimum_required(VERSION 2.8)

project(sha1 CXX)

option(BUILD_TESTS OFF)
option(BUILD_DEMO OFF)

if (NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif ()

add_library(sha1 STATIC sha1.cpp sha1.hpp)

install(TARGETS sha1
        DESTINATION lib)
install(FILES sha1.hpp
        DESTINATION include/sha1/)

if (BUILD_DEMO)
    add_executable(demo demo_sha1.cpp)
    target_link_libraries(demo sha1)
    install(TARGETS demo
            DESTINATION bin/)
endif ()

if (BUILD_TESTS)
    add_executable(test_sha1 test_sha1.cpp)
    target_link_libraries(test_sha1 sha1)
    install(TARGETS test_sha1
            DESTINATION bin/)
endif ()

set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 1)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_PROJECT_NAME "${CMAKE_PROJECT_NAME}")
include(CPack)
