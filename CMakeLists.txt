cmake_minimum_required(VERSION 3.22)

project(SMAN	VERSION 1.1
            	DESCRIPTION "SSH Client Manager (SMAN) allows you to easily connect to your SSH Servers using a simple user-defined list."
            	LANGUAGES C)

configure_file(src/version.h.in version.h)

add_executable(SMAN src/main.c)
add_library(connect src/connect.c)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(SMAN connect)
