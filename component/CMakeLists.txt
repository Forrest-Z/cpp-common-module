# 动态库单元测试设置
set(LIB_TEST_NAME component)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LIB_TEST_NAME}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#####################################
# package_inc
#####################################
file(GLOB_RECURSE PACKAGE_INC_component
  "include/*.h"	
)

message(STATUS "PACKAGE_INC_component")
foreach(file ${PACKAGE_INC_component})
  message(STATUS "${file}")
endforeach(file ${PACKAGE_INC_component})

#####################################
# package_src
#####################################
file(GLOB_RECURSE PACKAGE_SRC_component
  "src/*.cc"
)

message(STATUS "PACKAGE_SRC_component")
foreach(file ${PACKAGE_SRC_component})
  message(STATUS "${file}")
endforeach(file ${PACKAGE_SRC_component})

#####################################
# package_test
#####################################
file(GLOB_RECURSE ALL_TEST_component
 "src/*_test.cpp"
)
message(STATUS "ALL_TEST_component")
foreach(file ${ALL_TEST_component})
  message(STATUS "${file}")
endforeach(file ${ALL_TEST_component})


# 配置单元测试
################################
# GTest
################################
enable_testing()
include(GoogleTest)
find_package(GTest REQUIRED)
message("GTEST_INCLUDE_DIR=${GTEST_INCLUDE_DIR}")
message("GTEST_LIBRARIES=${GTEST_LIBRARIES}")

set(CMAKE_CXX_FLAGS "-std=c++11 -g -O0 -fprofile-arcs -ftest-coverage")
add_compile_options(-rdynamic -ggdb)

link_libraries(  ${GTEST_LIBRARIES})

add_executable(${LIB_TEST_NAME}
${PACKAGE_SRC_component}
  ${ALL_TEST_component}
)
target_link_libraries(${LIB_TEST_NAME}
  ${GTEST_LIBRARIES}
  -lpthread
)
