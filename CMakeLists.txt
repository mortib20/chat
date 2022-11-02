cmake_minimum_required(VERSION 3.24)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_C_CLANG_TIDY clang-tidy --use-color -checks=-*,portability-*,performace-*,clang-analyzer-*,bugprone-*)
set(CMAKE_C_STANDARD 99)

project(Chat C)

# Network
add_library(net STATIC ./include/net.c)
target_include_directories(net PUBLIC ./include)

# Client
add_executable(chatc ./src/client.c)
target_link_libraries(chatc net)

# Server
add_executable(chats ./src/server.c)
target_link_libraries(chats net)

# Install
install(TARGETS chatc chats DESTINATION ~/bin)