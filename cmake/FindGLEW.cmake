# input variables:
# GLEW_PATH - additional path for searching GLEW library
# output variables:
# GLEW_FOUND - system has GLEW library
# GLEW_INCLUDE_DIR
# GLEW_LIBRARY


if(GLEW_INCLUDE_DIR AND GLEW_LIBRARY)
    set(GLEW_FOUND TRUE)
else()
    find_package(PkgConfig)
    if(GLEW_PATH)
        set( ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:${GLEW_PATH}/lib/pkgconfig" )
    endif()

    if (PKG_CONFIG_FOUND)
        pkg_check_modules(_GLEW glew QUIET)
        if(NOT _GLEW_INCLUDE_DIRS OR NOT _GLEW_LIBRARY_DIRS)
            pkg_check_modules(_GLEW libglew QUIET)
            if(NOT _GLEW_INCLUDE_DIRS OR NOT _GLEW_LIBRARY_DIRS)
                pkg_check_modules(_GLEW GLEW QUIET)
                if(NOT _GLEW_INCLUDE_DIRS OR NOT _GLEW_LIBRARY_DIRS)
                    pkg_check_modules(_GLEW libGLEW QUIET)
                endif()
            endif()
        endif()
    endif()

    find_path(GLEW_INCLUDE_DIR
        NAMES GL/glew.h
        PATHS ${_GLEW_INCLUDE_DIRS} /usr/include /usr/local/include /opt/local/include /sw/include
            ${GLEW_PATH}/include
    )

    find_library(GLEW_LIBRARY
        NAMES glew GLEW
        PATHS ${_GLEW_LIBRARY_DIRS} /usr/lib64 /usr/lib /usr/local/lib /opt/local/lib /sw/lib
            ${GLEW_PATH}/lib ${GLEW_PATH}
    )

    if(GLEW_INCLUDE_DIR AND GLEW_LIBRARY)
        set(GLEW_FOUND TRUE)
    endif()

    if(GLEW_FOUND)
        if(NOT GLEW_FIND_QUIETLY)
            message(STATUS "GLEW found")
        endif()
    else()
        if(GLEW_FIND_REQUIRED)
            message(FATAL_ERROR "GLEW not found!")
        endif()
    endif()
endif()



