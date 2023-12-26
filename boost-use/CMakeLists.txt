# 动态库单元测试设置
project(boost-use)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_NAME}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED COMPONENTS serialization)
# find_package(Boost)

#####################################
# ${PROJECT_NAME}_INC
#####################################
file(GLOB_RECURSE ${PROJECT_NAME}_INC
  "include/*.h"	
)

message(STATUS "${PROJECT_NAME}_INC")
foreach(file ${${PROJECT_NAME}_INC})
  message(STATUS "${file}")
endforeach(file ${${PROJECT_NAME}_INC})

#####################################
# ${PROJECT_NAME}_SRC
#####################################
file(GLOB_RECURSE ${PROJECT_NAME}_SRC
  "src/*.cc"
)

message(STATUS "${PROJECT_NAME}_SRC")
foreach(file ${${PROJECT_NAME}_SRC})
  message(STATUS "${file}")
endforeach(file ${${PROJECT_NAME}_SRC})

#####################################
# package_test
#####################################
file(GLOB_RECURSE ${PROJECT_NAME}_TEST
 "src/*_test.cpp"
)
message(STATUS "${PROJECT_NAME}_TEST")
foreach(file ${${PROJECT_NAME}_TEST})
  message(STATUS "${file}")
endforeach(file ${${PROJECT_NAME}_TEST})


# 配置单元测试
################################
# GTest
################################
enable_testing()
include(GoogleTest)
find_package(GTest REQUIRED)
message("GTEST_INCLUDE_DIR=${GTEST_INCLUDE_DIR}")
message("GTEST_LIBRARIES=${GTEST_LIBRARIES}")

set(CMAKE_CXX_FLAGS "-std=c++11 -g -O0 -rdynamic -fprofile-arcs -ftest-coverage")
add_compile_options(-rdynamic -ggdb)

link_libraries(  ${GTEST_LIBRARIES}   ${Boost_LIBRARIES})

add_executable(${PROJECT_NAME} "src/test_main.cc"
${${PROJECT_NAME}_SRC}
  ${${PROJECT_NAME}_TEST}
)

target_link_libraries(${PROJECT_NAME}
  ${GTEST_LIBRARIES}
  -lpthread -ldl
  ${Boost_LIBRARIES}
)
