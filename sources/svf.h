#ifndef SVF_H
#define SVF_H

#include "application.h"

#define RUN_APPLICATION(application_name) \
int main(/* int argc, char *argv[] */) { \
    try { \
        std::unique_ptr<svf::Application> app(new application_name()); \
\
        bool running = true; \
        while ( running ) { \
            app->doRendering(); \
\
            SDL_Event event; \
            while ( SDL_PollEvent(&event) ) { \
                switch ( event.type ) { \
                    case SDL_QUIT: { \
                        running = false; \
                        break; \
                    } \
                    case SDL_KEYDOWN: { \
                        switch ( event.key.keysym.sym ) { \
                            case SDLK_ESCAPE: \
                                running = false; \
                                break; \
                        } \
                        break; \
                    } \
                    default: { \
                        break; \
                    } \
                } \
            } \
        } \
    } catch ( const svf::Error& error ) { \
        std::cerr << "Can not create application! Reason: " << error.what() << std::endl; \
        return 1; \
    } \
\
    return 0; \
}

#endif /* end of include guard: SVF_H */
