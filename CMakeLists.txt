cmake_minimum_required(VERSION 3.28.2)

include(../sdk/config.cmake)
project(sieelf_sie_launcher C)

include_directories("../libsie/src/include")
link_libraries(crt crt_helper c gcc m z png ft sie)
file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(SieLauncher_ELKA ${SOURCES})
target_sdk_setup(SieLauncher_ELKA ELKA)
target_link_directories(SieLauncher_ELKA PUBLIC "../libsie/build/lib/ELKA")
target_compile_options(SieLauncher_ELKA BEFORE PUBLIC -std=gnu99 -Wall -Werror)
