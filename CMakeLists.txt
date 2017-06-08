cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(PROJECT svf)

project(${PROJECT} CXX C)
set(PROJECT_DESCRIPTION "Simple video framework")

if(NOT DEFINED INSTALL_PATH)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")
else()
    set(CMAKE_INSTALL_PREFIX "${INSTALL_PATH}")
endif()
set(INSTALL_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include")
set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib")
set(PKG_CONFIG_LIBS "-L${INSTALL_LIB_DIR} -lsvf")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#find_package(Git REQUIRED)
#include(GetVersionFromGit)
#set(PROJ_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(PROJ_VERSION "1.0.0")
set(PROJ_REQUIRES "SDL2")

set(ADDITIONAL_FLAGS "-pedantic -Wall -Wextra")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS_DEBUG "-O0 -g3 ${ADDITIONAL_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -std=c++11 ${ADDITIONAL_FLAGS}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_C_FLAGS_RELEASE "-O3 ${ADDITIONAL_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -std=c++11 ${ADDITIONAL_FLAGS}")
elseif (NOT CMAKE_BUILD_TYPE STREQUAL "Release" AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "-O3 ${ADDITIONAL_FLAGS}")
    set(CMAKE_CXX_FLAGS "-O3 -std=c++11 ${ADDITIONAL_FLAGS}")
endif()

set(SOURCE_DIRS "${CMAKE_SOURCE_DIR}/sources")
#set(TEST_SOURCE_DIRS "${CMAKE_SOURCE_DIR}/tests_sources")
#set(ATEST_SOURCE_DIRS "${CMAKE_SOURCE_DIR}/atests_sources")

find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)

#find_package(Doxygen)
#if(NOT DOXYGEN_FOUND)
    #message(WARNING "Doxygen, not found. Can't create documentation")
#endif()

#if(NOT EXISTS ${CMAKE_SOURCE_DIR}/Doxyfile)
    #message(WARNING "Config for doxygen not found. If you want to make documentation then add file with name 'Doxyfile' in ${CMAKE_SOURCE_DIR}.  Note: doxygen must generate documentation in ${CMAKE_SOURCE_DIR}/docs/html")
#endif()

include_directories(${OPENGL_INCLUDE_DIR} ${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})

aux_source_directory(${SOURCE_DIRS} SOURCES)

add_library(${PROJECT} SHARED ${SOURCES})
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties( ${PROJECT} PROPERTIES DEBUG_POSTFIX "-d")
endif()
target_link_libraries(${PROJECT} ${CMAKE_THREAD_LIBS_INIT} ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${GLEW_LIBRARY} X11)

#if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    #add_executable(${PROJECT}_tests ${TEST_SOURCES} ${SOURCES})
    #set_target_properties(
        #${PROJECT}_tests
        #PROPERTIES
        #COMPILE_FLAGS "-DACTOR_SYSTEM_TEST"
        #RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/debug_tests
    #)
    #target_link_libraries(${PROJECT}_tests ${GTEST_LIBRARY} ${GMOCK_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
#elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    #add_executable(${PROJECT}_tests ${TEST_SOURCES} ${SOURCES})
    #set_target_properties(
        #${PROJECT}_tests
        #PROPERTIES
        #COMPILE_FLAGS "-DACTOR_SYSTEM_TEST"
        #RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/release_tests
    #)
    #target_link_libraries(${PROJECT}_tests ${GTEST_LIBRARY} ${GMOCK_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
#elseif (NOT CMAKE_BUILD_TYPE STREQUAL "Release" AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    #add_executable(${PROJECT}_tests EXCLUDE_FROM_ALL ${TEST_SOURCES} ${SOURCES})
    #set_target_properties(
        #${PROJECT}_tests
        #PROPERTIES
        #COMPILE_FLAGS "-DACTOR_SYSTEM_TEST"
        #RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
    #)
    #target_link_libraries(${PROJECT}_tests ${GTEST_LIBRARY} ${GMOCK_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

    #add_custom_target(build_tests DEPENDS ${PROJECT}_tests)
#endif()

configure_file(
    "${CMAKE_SOURCE_DIR}/pkgconfig.pc.cmake"
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc"
)
install(TARGETS ${PROJECT} DESTINATION ${INSTALL_LIB_DIR})
install(DIRECTORY ${SOURCE_DIRS}/ DESTINATION ${INSTALL_INCLUDE_DIR}/svf FILES_MATCHING PATTERN "*.h")
install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc" DESTINATION "${INSTALL_LIB_DIR}/pkgconfig")

add_custom_target(debug
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Debug
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/Debug
    ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=Debug ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/Debug --target all)

add_custom_target(release
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Release
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/Release
        ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=Release ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/Release --target all)

add_subdirectory("${CMAKE_SOURCE_DIR}/example")
add_custom_target(example)
add_dependencies(example svf_example)
