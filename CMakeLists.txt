cmake_minimum_required(VERSION 3.22)

project(SMAN	VERSION 1.0
            	DESCRIPTION "SSH Client Manager (SMAN) allows you to easily connect to your SSH Servers using a simple user-defined list."
            	LANGUAGES C)

add_executable(SMAN src/main.c)
add_library(connect src/connect.c)
target_include_directories(connect PRIVATE src/)

target_link_libraries(SMAN connect)
