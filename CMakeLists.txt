cmake_minimum_required(VERSION 3.7)
project(structures)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        library.c
        library.h
        vector.c
        vector.h
        str.c
        str.h
        list.c
        list.h
        dict.c
        dict.h
        test/vendor/unity.c
        test/vendor/unity.h
        test/vendor/unity_internals.h
)

add_executable(tests test/structures.c ${SOURCE_FILES})
add_library(structures ${SOURCE_FILES})
target_link_libraries(tests m)
