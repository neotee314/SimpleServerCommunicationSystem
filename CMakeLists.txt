cmake_minimum_required(VERSION 3.26)

project(SimpleTCPKeyValueServer C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(SimpleTCPKeyValueServer src/main.c
        src/utils.c
        src/protocol.c
        src/keyValueStore.c
        src/sub.c
        include/utils.h
        include/protocol.h
        include/keyValueStore.h
        include/main.h
        include/sub.h
)
