cmake_minimum_required (VERSION 3.0)
project (commoner
         VERSION 1.0.0
         LANGUAGES C)
add_subdirectory(src)

include(GNUInstallDirs)


add_custom_target(distclean
                  COMMAND make clean
                  COMMAND rm -rf *
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

add_custom_target(expand-vars
                  COMMAND echo ${CMAKE_SOURCE_DIR}
                  COMMAND echo ${CMAKE_CURRENT_SOURCE_DIR}
                  COMMAND ls)
