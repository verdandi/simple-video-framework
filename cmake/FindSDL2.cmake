# input variables:
# SDL2_PATH - additional path for searching SDL2 library
# output variables:
# SDL2_FOUND - system has SDL2 library
# SDL2_INCLUDE_DIR
# SDL2_LIBRARY


if(SDL2_INCLUDE_DIR AND SDL2_LIBRARY)
    set(SDL2_FOUND TRUE)
else()
    find_package(PkgConfig)
    if(SDL2_PATH)
        set( ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:${SDL2_PATH}/lib/pkgconfig" )
    endif()

    if (PKG_CONFIG_FOUND)
        pkg_check_modules(_SDL2 sdl2 QUIET)
        if(NOT _SDL2_INCLUDE_DIRS OR NOT _SDL2_LIBRARY_DIRS)
            pkg_check_modules(_SDL2 libsdl2 QUIET)
            if(NOT _SDL2_INCLUDE_DIRS OR NOT _SDL2_LIBRARY_DIRS)
                pkg_check_modules(_SDL2 SDL2 QUIET)
                if(NOT _SDL2_INCLUDE_DIRS OR NOT _SDL2_LIBRARY_DIRS)
                    pkg_check_modules(_SDL2 libSDL2 QUIET)
                endif()
            endif()
        endif()
    endif()

    find_path(SDL2_INCLUDE_DIR
        NAMES SDL2/SDL.h sdl2/sdl.h SDL2/sdl.h sdl2/SDL.h
        PATHS ${_SDL2_INCLUDE_DIRS} /usr/include /usr/local/include /opt/local/include /sw/include
            ${SDL2_PATH}/include
    )

    find_library(SDL2_LIBRARY
        NAMES sdl2 SDL2
        PATHS ${_SDL2_LIBRARY_DIRS} /usr/lib64 /usr/lib /usr/local/lib /opt/local/lib /sw/lib
            ${SDL2_PATH}/lib ${SDL2_PATH}
    )

    if(SDL2_INCLUDE_DIR AND SDL2_LIBRARY)
        set(SDL2_FOUND TRUE)
    endif()

    if(SDL2_FOUND)
        if(NOT SDL2_FIND_QUIETLY)
            message(STATUS "SDL2 found")
        endif()
    else()
        if(SDL2_FIND_REQUIRED)
            message(FATAL_ERROR "SDL2 not found!")
        endif()
    endif()
endif()



