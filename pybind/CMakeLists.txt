# 动态库单元测试设置
project(example)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_NAME}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# include pybind
# $(python3 -m pybind11 --includes)
include(/root/miniconda3/lib/python3.11/site-packages/pybind11/share/cmake/pybind11/pybind11Config.cmake)

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


set(CMAKE_CXX_FLAGS "-std=c++11 -g -O0 -rdynamic -fPIC")
add_compile_options(-rdynamic -ggdb)

pybind11_add_module(example src/example.cc)
pybind11_add_module(testclass src/testclass.cc)

