cmake_minimum_required(VERSION 3.12.1)
project(Visualisator C)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES
#        libft/*.h
#        libft/*.c
        *.h
        *.c)

aux_source_directory(libft LBFT_SRC)
add_library(ft STATIC ${LBFT_SRC})


add_executable(Visualisator
        ${SOURCES})

target_link_libraries(Visualisator ft)

#set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror")
#set(GCC_COVERAGE_COMPILE_FLAGS "-Werror -Wextra -Wall")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
target_link_libraries(Visualisator -lmlx "-framework OpenGL" "-framework AppKit")

