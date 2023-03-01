#!/bin/bash

# test_file=./Build/test/common/bin/project_test

### use valgrind
test_file="valgrind -v --leak-check=full --show-leak-kinds=all ./Build/test/common/bin/project_test"

${test_file}

# ${test_file}  --gtest_filter=sample_test.add_test


