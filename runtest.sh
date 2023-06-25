#!/bin/bash

# test_file=./Build/test/common/bin/project_test

### use valgrind
test_file="valgrind -v --leak-check=full --show-leak-kinds=definite,indirect ./Build/test/common/bin/project_test"

# ${test_file}

# ${test_file}  --gtest_filter=sample_test.add_test

###
# ${test_file}  --gtest_filter=backtrace_test.segv
# ${test_file}  --gtest_filter=log_test.printf

# ${test_file}  --gtest_filter=common.MsgQueueTest

# ${test_file}  --gtest_filter=common.hex_to_chararray
# ${test_file}  --gtest_filter=common.chararray_to_hex

test_file_component="valgrind -v --leak-check=full --show-leak-kinds=definite,indirect ./Build/component/component/bin/component"
${test_file_component} --gtest_filter=threadpool.thread_manager
