#####################################
# head
#####################################
cmake_minimum_required(VERSION 3.15.0)

message("#####################################")
message("PROJECT_NAME = ${PROJECT_NAME}")
message("#####################################")

project(${PROJECT_NAME})

#####################################
# set log4cpp path
#####################################
if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64" OR CMAKE_CROSSCOMPILING)
    message("this is aarch64 cpu")
    set(3rdparty_log4cpp_lib ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/log4cpp_lib/aarch64)
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
	message("this is x86_64 cpu")
  set(3rdparty_log4cpp_lib ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/log4cpp_lib/x86_64)
endif()


#####################################
# include
#####################################
include_directories(/usr/include)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${3rdparty_log4cpp_lib}/include)

#####################################
# package_inc
#####################################
file(GLOB_RECURSE PACKAGE_INC
  "include/*"	
)

message(STATUS "PACKAGE_INC")
foreach(file ${PACKAGE_INC})
  message(STATUS "${file}")
endforeach(file ${PACKAGE_INC})

#####################################
# package_src
#####################################
file(GLOB_RECURSE PACKAGE_SRC
  "src/*.cc"
)

message(STATUS "PACKAGE_SRC")
foreach(file ${PACKAGE_SRC})
  message(STATUS "${file}")
endforeach(file ${PACKAGE_SRC})


#####################################
# link and compile
#####################################
set(CMAKE_CXX_FLAGS "-std=c++11 -g -O0 -fprofile-arcs -ftest-coverage")
add_compile_options(-rdynamic)

link_libraries("${3rdparty_log4cpp_lib}/liblog4cpp.a")

add_library(${PROJECT_NAME} SHARED ${PACKAGE_SRC})

target_link_libraries(${PROJECT_NAME} 
${3rdparty_log4cpp_lib}/liblog4cpp.a
-lboost_system
-lboost_thread
-pthread)

#####################################
# install
#####################################
INSTALL (
  DIRECTORY include/${PROJECT_NAME}
  DESTINATION ${install_path}/include
  PATTERN "config.h" EXCLUDE
  PATTERN ".svn" EXCLUDE
  PATTERN "*.am" EXCLUDE
  PATTERN "*.in" EXCLUDE
)

INSTALL (
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${install_path}/lib
)


#####################################
# 增加单元测试
#####################################
add_subdirectory(test)


#####################################
# 代码规范化检查 cpplint
#####################################
file(GLOB LINT_SRC
          ${PACKAGE_INC}
          ${PACKAGE_SRC}
)

foreach(v ${LINT_SRC})
  # execute_process(COMMAND cpplint --filter=-legal/copyright,-build/include_order,-readability/casting,-build/c++11,
  # -build/include_subdir,-runtime/references --quiet ${v} )
endforeach(v)

add_subdirectory(component)
add_subdirectory(boost-use)