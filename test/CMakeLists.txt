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
# GFalgs
################################
# find_package(GFlags REQUIRED)
# message("GFLAGS_INCLUDE_DIRS=${GFLAGS_INCLUDE_DIRS}")
# message("GFLAGS_LIBRARIES=${GFLAGS_LIBRARIES}")

################################
# GLog
################################
# find_package(GLog REQUIRED)
# message("GLOG_INCLUDE_DIRS=${GLOG_INCLUDE_DIRS}")
# message("=${GLOG_LIBRARIES}")

################################
# GTest
################################
enable_testing()
include(GoogleTest)
find_package(GTest REQUIRED)
message("GTEST_INCLUDE_DIR=${GTEST_INCLUDE_DIR}")
message("GTEST_LIBRARIES=${GTEST_LIBRARIES}")


add_executable(${LIB_TEST_NAME}
  ${ALL_TEST}
)
link_directories(${build_dir})
target_link_libraries(${LIB_TEST_NAME}
  ${GTEST_LIBRARIES}
  # ${GLOG_LIBRARIES}
  # ${GFLAGS_LIBRARIES}
  ${PROJECT_NAME}
  -lboost_system
  -lboost_thread
)

gtest_discover_tests(${LIB_TEST_NAME}
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  -lglog
  -lpthread
  -lgcov -lz
)
