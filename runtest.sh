#!/bin/bash

# test_file=./Build/test/common/bin/project_test

### use valgrind
test_file="valgrind --leak-check=full ./Build/test/common/bin/project_test"

${test_file}

# ${test_file}  --gtest_filter=sample_test.add_test


