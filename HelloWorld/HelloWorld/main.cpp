// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <iostream>

GLFWwindow* window;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  // When a user presses the escape key, we set the WindowShouldClose property to true, 
  // closing the application
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void initializeGLFW()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // NB cannot be resized

}

bool initAndCreateGLFWWindow()
{
  initializeGLFW();
  window = glfwCreateWindow(800, 600, "Hello World", nullptr, nullptr);
  if (window == nullptr)
  {
    std::cout << "Failed to create GLFW Window" << std::endl;
    glfwTerminate();
    return false;
  }

  // bind context, must be called before initialize GLEW
  glfwMakeContextCurrent(window);
  return true;
}

bool initGLEW()
{
  glewExperimental = GL_TRUE;
  auto err = glewInit();
  if (err != GLEW_OK)
  {
    std::cout << "Failed to initialize GLEW, error = " << glewGetErrorString(err) << std::endl;
    return false;
  }
  
  return true;
}

void setViewPort()
{
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  ///glViewport first 2 parameters are the location of the lower left corner of the window. 
  ///The third and fourth parameter set the width and height of the rendering window in pixels (use GLFW provided numbers to also work with high DPI screens)
  glViewport(0, 0, width, height);
}

void runWndProc() 
{  
  // set keypress handler
  glfwSetKeyCallback(window, key_callback); 

  //event loop
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
  
  // program is closing down, terminate opengl  
  glfwTerminate();
}

int main()
{
  if (!initAndCreateGLFWWindow() || !initGLEW()) 
    return -1;

  setViewPort();
  runWndProc();
  
  return 0;
}


