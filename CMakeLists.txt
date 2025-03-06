cmake_minimum_required(VERSION 3.30)
project(turing_machine C)

set(CMAKE_C_STANDARD 17)

add_executable(
        turing_machine
        main.c
        string.h
        string.c
        file.h
        file.c
        result.h
        result.c
        list.h
        list.c
        flow.c
        flow.h
        transition.c
        transition.h
        tm.c
        tm.h
)

target_compile_options(turing_machine PRIVATE -Wall -Wextra -Werror)

include(CTest)

add_executable(dtm test/tm.c)
add_test(NAME dtm COMMAND dtm)