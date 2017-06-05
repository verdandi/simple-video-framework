#ifndef SIMPLE_VIDEO_FRAMEWORK_APPLICATION_H_
#define SIMPLE_VIDEO_FRAMEWORK_APPLICATION_H_

/*
 * developed by: Kuksov Pavel
 * e-mail: aimed.fire@gmail.com
 */

#include <memory>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include <GL/glew.h>
#include <GL/glxew.h>

#include "error.h"

namespace svf {

class Application {
public:
    Application();
    Application(const std::string& window_name);
    Application(int window_width, int window_height);
    Application(const std::string& window_name, int window_width, int window_height);

    void doRendering();

    virtual ~Application();

    virtual void render(float current_time);

private:
    static const int WINDOW_WIDTH = 640;
    static const int WINDOW_HEIGHT = 480;

    std::chrono::high_resolution_clock::time_point start_;
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window_;
    SDL_GLContext context_;

    void initVideoSubsystem(const std::string& window_name, int window_width, int window_height);
};//end of declaration class Application

} /* svf */

#endif /* end of include guard: SIMPLE_VIDEO_FRAMEWORK_APPLICATION_H_ */
