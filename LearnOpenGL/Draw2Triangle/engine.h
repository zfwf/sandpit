#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

/// A basic engine to encapsulate OpenGL calls and hosts the program event loop to handle interactions
class CEngine {
public:
  bool init(int width, int height, const char* windowTitle);
  void run();
  virtual ~CEngine(); // virtual destructor

protected:
  

private: 
  GLFWwindow* window = nullptr;
  GLuint VAO = 0;
  GLuint VBO = 0;
  GLuint shaderProgram = 0;

  void initGLFW();
  bool initAndCreateGLFWWindow(int width, int height, const char* windowTitle);
  bool initGLEW();
  
  void setViewPort();
  bool createShaders();
  void prepVertexData();
  void render();
  
  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};


