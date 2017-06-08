# Simple-video-framework
### Short description
This is simple framework which allows to concentare on working with OpenGL without necessity to know any details (window creation, evaluation loop and etc.)

### Requirments
- OS Linux
- gcc v.8.4.2 or more
- cmake v.2.8 or more
- GNU make v.4.0 or more

### Dependencies
- SDL2
- GLEW

### Build
1. cd <root_directory_of_project>
2. mkdir build && cd build
3. cmake [-DSDL2_PATH=/full/path/to/sdl2/library] [-DGLEW_PATH=/full/path/to/glew/library] [-DINSTALL_PATH=/full/path/to/the/install/dir] ..
  - -DGLEW_PATH - defines additional custom path for searching GLEW library
  - -DSDL2_PATH - defines additional custom path for searching SDL2 library
  - -DINSTALL_PATH - defines install prefix. If this parameter defined then library will be installed in directory <INSTALL_PATH>/bali else in directory <root_dir_of_project>/install/bali
4. It is possibile to create following builds:
  - make && make install - create shared library and install it.
  - make example - create build examples
