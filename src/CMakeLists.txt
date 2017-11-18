cmake_minimum_required (VERSION 2.6)
add_library(commoner SHARED common.c)

# declare headers for commoner
target_include_directories(commoner PUBLIC
                           $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/common.h>)

add_custom_command(OUTPUT commoner.h
                   COMMAND ls
                   #COMMAND rename .h er.h
                   WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build/src)

add_custom_target(all
                  COMMAND cp ${CMAKE_SOURCE_DIR}/src/common.h
                  ${CMAKE_SOURCE_DIR}/src/commoner.h)

install(TARGETS commoner
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

#install(TARGETS commoner.h
        #PUBLIC_HEADER DESTINATION include)
