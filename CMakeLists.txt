cmake_minimum_required(VERSION 3.30)
project(AlgoStudy)

#解决奇数个数中文在msvc上无法编译utf-8不带bom的代码文件
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(CMAKE_CXX_STANDARD 20)

#获取algo文件夹内所有的cpp文件，以文件名作为target
file(GLOB_RECURSE ALGO_SOURCES "algo/*.cpp")
foreach (ALGO_SOURCE ${ALGO_SOURCES})
    get_filename_component(ALGO_TARGET ${ALGO_SOURCE} NAME_WE)
    add_executable(${ALGO_TARGET} ${ALGO_SOURCE})
endforeach ()


