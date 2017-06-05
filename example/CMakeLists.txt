cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(PROJECT svf_example)

project(${PROJECT} CXX C)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "../cmake/")

aux_source_directory("${CMAKE_SOURCE_DIR}/example" EXAMPLE_SOURCES)
add_executable(${PROJECT} EXCLUDE_FROM_ALL ${SOURCES} ${EXAMPLE_SOURCES})
target_link_libraries(${PROJECT} ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(
    ${PROJECT}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/example/bin
)
target_link_libraries(${PROJECT} ${CMAKE_THREAD_LIBS_INIT} ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${GLEW_LIBRARY} X11)
target_include_directories(${PROJECT} PUBLIC "../sources")
