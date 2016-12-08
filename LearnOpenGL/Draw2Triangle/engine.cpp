#include "engine.h"
#include <iostream>

void CEngine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  // When a user presses the escape key, we set the WindowShouldClose property to true, 
  // closing the application
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void CEngine::initGLFW()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // NB cannot be resized

}

bool CEngine::initAndCreateGLFWWindow(int width, int height, const char* windowTitle)
{
  initGLFW();
  window = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);
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

bool CEngine::initGLEW()
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

bool CEngine::init(int width, int height, const char* windowTitle)
{
  if (!initAndCreateGLFWWindow(width, height, windowTitle) || !initGLEW())
    return false;

  setViewPort();
  if (!createShaders())
    return false;

  prepVertexData();

  return true;
}

void CEngine::setViewPort()
{
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  ///glViewport first 2 parameters are the location of the lower left corner of the window. 
  ///The third and fourth parameter set the width and height of the rendering window in pixels (use GLFW provided numbers to also work with high DPI screens)
  glViewport(0, 0, width, height);
}

const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

bool  CEngine::createShaders()
{
  GLint success;
  GLchar infoLog[512];

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "Vertex shader compilation failed:\n" << infoLog << std::endl;
    return false;
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "Fragment shader compilation:\n" << infoLog << std::endl;
    return false;
  }

  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "Link shader to program failed:\n" << infoLog << std::endl;
    return false;
  }

  // can delete shader once linked
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return true;
}


void CEngine::prepVertexData()
{
  GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
  };

  glGenVertexArrays(1, &VAO); // 1. gnerate vertex array object
  glBindVertexArray(VAO); // 2. bind vertex array, this will be the array to store the vertex buffers


  glGenBuffers(1, &VBO); // 1. generate vertex buffer object
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // 2. bind to vertex array (if do not gen vertex array above, it will go to an inbuilt one)
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 3. copy vertices data to VBO, which now is bound to a vertex array

                                                                             // 4. Then set our vertex attributes pointers for the "position" vertex attribute. vertex consist of 3 vertices, starting at 0 position in vertices array. each vertex is 3 float variable, no padding between vertices
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0); // enable the above attribute (which is at postion 0 in attribute array)

  glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
  glBindVertexArray(0); // unbind the VAO after setup
}


void CEngine::render()
{
  // Clear the colorbuffer
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(shaderProgram); // choose the program we want to use
  glBindVertexArray(VAO); // bind

  glDrawArrays(GL_TRIANGLES, 0, 3); // draw as triangle, draw the vertex starting at first, finish at after 3 is drawn
  glBindVertexArray(0); //unbind
}

void CEngine::run()
{
  // set keypress handler
  glfwSetKeyCallback(window, key_callback);

  //event loop
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    render();
    glfwSwapBuffers(window);
  }  
}

CEngine::~CEngine() {
  // Properly de-allocate all resources once they've outlived their purpose
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  
  // terminate opengl  
  glfwTerminate();
}
