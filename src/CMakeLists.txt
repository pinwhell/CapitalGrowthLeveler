add_library(PGL "CGL.cpp")

target_include_directories(PGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_subdirectory(cli)