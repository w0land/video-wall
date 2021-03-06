project(CXX)

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

option(BUILD_WITH_UNIT_TESTS "Build unit tests" ON)
option(BUILD_WITH_INTEGRATION_TESTS "Build integration tests" OFF)
option(BUILD_WITH_EXAMPLES "Build examples folder" OFF)
option(BUILD_WITH_COVERAGE "Build examples folder" OFF)

include(CEFBinaryDistribution)
include(Compilers)
include(Valgrind)

set(CMAKE_CXX_STANDARD 14)

if(BUILD_WITH_COVERAGE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
    set(COVERAGE_EXCLUDES '${CMAKE_SOURCE_DIR}/3rdParty/*'
        '/usr/include/*' '${CMAKE_SOURCE_DIR}/integration_tests/*' '${CMAKE_SOURCE_DIR}/tests/*'
        '${CEF_ROOT}/*'
        )
    setup_target_for_coverage(
        NAME coverage
        EXECUTABLE ctest
    )
else()
    add_custom_target(coverage
        COMMAND cmake -E echo "Coverage disabled, run cmake . -DBUILD_WITH_COVERAGE=ON to enable")

endif()

add_subdirectory(3rdParty)

add_subdirectory(srcs)
if(BUILD_WITH_UNIT_TESTS)
    enable_testing()
    include(GTEST_ADD_TESTS)
    add_subdirectory(tests)
endif()

if(BUILD_WITH_INTEGRATION_TESTS)
    add_subdirectory(integration_tests)
endif()

if(BUILD_WITH_EXAMPLES)
    add_subdirectory(examples)
endif()

