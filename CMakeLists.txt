cmake_minimum_required(VERSION 3.30)
project(tm C)

set(CMAKE_C_STANDARD 17)

add_executable(
        tm
        src/main.c
        src/dtm.c
)
target_compile_options(tm PRIVATE -Wall -Wextra -Werror -Wconversion)

include(CTest)

add_executable(
        tm_test
        test/main.c
        src/dtm.c
)
target_compile_options(tm_test PRIVATE -Wall -Wextra -Werror -Wconversion)
add_test(NAME tm_test COMMAND tm_test)