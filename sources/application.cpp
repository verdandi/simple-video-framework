#include "application.h"

#include <iostream>

namespace svf {

Application::Application():
    start_(std::chrono::high_resolution_clock::now()),
    window_(nullptr, SDL_DestroyWindow), context_(nullptr)
{
    initVideoSubsystem("SVF Application", WINDOW_WIDTH, WINDOW_HEIGHT);
}

Application::Application(const std::string& window_name):
    start_(std::chrono::high_resolution_clock::now()),
    window_(nullptr, SDL_DestroyWindow),
    context_(nullptr)
{
    initVideoSubsystem(window_name, WINDOW_WIDTH, WINDOW_HEIGHT);
}

Application::Application(const std::string& window_name, int window_width, int window_height):
    start_(std::chrono::high_resolution_clock::now()),
    window_(nullptr, SDL_DestroyWindow),
    context_(nullptr)
{
    initVideoSubsystem(window_name, window_width, window_height);
}

Application::Application(int window_width, int window_height):
    start_(std::chrono::high_resolution_clock::now()),
    window_(nullptr, SDL_DestroyWindow),
    context_(nullptr)
{
    initVideoSubsystem("SVF Application", window_width, window_height);
}

void Application::initVideoSubsystem(const std::string& window_name, int window_width, int window_height) {

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        std::string error_message = "Impossible to init SDL2 (";
        error_message += SDL_GetError();
        error_message += ")";
        throw Error(error_message);
    }

    window_.reset(::SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width,
                                   window_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL));

    if ( window_ == nullptr ) {
        std::string error_message = "Impossible to create window (";
        error_message += SDL_GetError();
        error_message += ")";
        throw Error(error_message);
    }

    context_ = SDL_GL_CreateContext(window_.get());
    if ( context_ == nullptr ) {
        std::string error_message = "Impossible to create context (";
        error_message += SDL_GetError();
        error_message += ")";
        throw Error(error_message);
    }

    GLenum status = glewInit();
    if ( status != GLEW_OK ) {
        std::string error_message = "Impossible to init GLEW library (";
        error_message += (const char*)glewGetErrorString(status);
        error_message += ")";

        throw Error(error_message);
    }

    std::cerr << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
}

void Application::doRendering() {
    auto time = std::chrono::high_resolution_clock::now();
    render(std::chrono::duration_cast<std::chrono::milliseconds>(time - start_).count() / 1000.0);

    glFlush();
    SDL_GL_SwapWindow(window_.get());
}

void Application::render(float) {}

Application::~Application() {
    SDL_GL_DeleteContext(context_);
    window_.reset();
    SDL_Quit();
}

} /* svf */
