# 动态库单元测试设置
set(LIB_TEST_NAME project_test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_NAME}/bin)

#####################################
# package_test
#####################################
file(GLOB_RECURSE ALL_TEST
  "*.cc"
)
message(STATUS "ALL_TEST")
foreach(file ${ALL_TEST})
  message(STATUS "${file}")
endforeach(file ${ALL_TEST})


# 配置单元测试
################################
# GTest
################################
enable_testing()
include(GoogleTest)
find_package(GTest REQUIRED)
message("GTEST_INCLUDE_DIR=${GTEST_INCLUDE_DIR}")
message("GTEST_LIBRARIES=${GTEST_LIBRARIES}")

set(CMAKE_CXX_FLAGS "-std=c++11 -g -O0")
set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
add_compile_options(-rdynamic -ggdb)

add_executable(${LIB_TEST_NAME}
  ${ALL_TEST}
)
link_directories(${build_dir})
target_link_libraries(${LIB_TEST_NAME}
  ${GTEST_LIBRARIES}
  ${PROJECT_NAME}
  -lboost_system
  -lboost_thread
)

# gtest_discover_tests(${LIB_TEST_NAME}
#   WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
#   # -lglog
#   -lpthread
#   # -lgcov 
#   # -lz
# )
