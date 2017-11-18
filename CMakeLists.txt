cmake_minimum_required (VERSION 2.6)
project (commoner
         LANGUAGES C)
add_subdirectory(src)

add_custom_target(distclean
                  COMMAND make clean
                  COMMAND rm -rf *
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
