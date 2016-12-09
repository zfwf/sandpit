#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include "model.h"

/// A basic engine to encapsulate OpenGL calls and hosts the program event loop to handle interactions
class CEngine {
public:
  bool init(int width, int height, const char* windowTitle);
  void setScene(CScene * models);
  void run();
  virtual ~CEngine(); // virtual destructor

protected:
  

private: 
  GLFWwindow* window = nullptr;
  CScene* scene;

  void initGLFW();
  bool initAndCreateGLFWWindow(int width, int height, const char* windowTitle);
  bool initGLEW();
  void createModels();
  void setViewPort();
  bool createShaders();
  void prepVertexData();
  void render();
  
  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};


