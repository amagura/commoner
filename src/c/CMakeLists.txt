cmake_minimum_required (VERSION 2.6)
add_library(common src/common.c)
add_executable(test, test/test.c)

add_custom_command(TARGET common
                   POST_BUILD
                   COMMAND ./test)
