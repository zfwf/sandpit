#include "model.h"
#include <vector>
#include <iostream>



//void clearView(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha);
//void 

void CModel::setVertices(std::vector<GLfloat>& vertices)
{
  this->vertices = vertices;

  // get vertices into VBO
  if (VAO == 0)
    glGenVertexArrays(1, &VAO); // 1. gnerate vertex array object

  glBindVertexArray(VAO); // 2. bind vertex array, this will be the array to store the vertex buffers

  if (VBO != 0)
    glDeleteBuffers(1, &VBO);

  glGenBuffers(1, &VBO); // 1. generate vertex buffer object
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // 2. bind to vertex array (if do not gen vertex array above, it will go to an inbuilt one)
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat), this->vertices.data(), GL_STATIC_DRAW); // 3. copy vertices data to VBO, which now is bound to a vertex array

  // 4. Then set our vertex attributes pointers for the "position" vertex attribute. vertex consist of 3 vertices, starting at 0 position in vertices array. each vertex is 3 float variable, no padding between vertices
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0); // enable the above attribute (which is at postion 0 in attribute array)
  glBindVertexArray(0); // unbind the VAO after setup
}


bool CModel::compileShaders(const char* vertexShaderSource, const char* fragmentShaderSource)
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

bool CModel::setShaders(const char* vertexShaderSource, const char* fragmentShaderSource)
{
  return compileShaders(vertexShaderSource, fragmentShaderSource);
}

void CModel::setDrawLoopFuncs(void(*clear)(), void(*draw)())
{
  clearBufferFunc = clear;
  drawFunc = draw;
}

void CModel::render()
{
  // clear the screen buffer
  clearBufferFunc();
  
  glUseProgram(shaderProgram); // choose the program we want to use
  glBindVertexArray(VAO); // bind
  
  //draw
  drawFunc();

  glBindVertexArray(0); //unbind
}



CModel::~CModel()
{
  if (VAO != 0)
    glDeleteVertexArrays(1, &VAO);

  if (VBO != 0)
    glDeleteBuffers(1, &VBO);

  if (EBO != 0)
    glDeleteBuffers(1, &EBO);
}


C2TriangleModel::C2TriangleModel()
{
  prep2Triangles();
  createShaders();
}


void C2TriangleModel::prep2Triangles()
{
  std::vector<GLfloat> triangles = {
    0.5F,   0.5F,  0.0F,
    1.0F,   -0.5F, 0.0F,
    0.2F,   -0.5F, 0.0F,
    -0.2F,  -0.5F, 0.0F,
    -0.5F,  0.5F,  0.0F,
    -1.0F,  -0.5F, 0.0F
  };

  setVertices(triangles);
}

bool C2TriangleModel::createShaders()
{
  GLchar* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";

  GLchar* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

  auto ret = compileShaders(vertexShaderSource, fragmentShaderSource);
  return ret;
}

void C2TriangleModel::render()
{
  // Clear the colorbuffer
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(shaderProgram); // choose the program we want to use
  glBindVertexArray(VAO); // bind
  
  glDrawArrays(GL_TRIANGLES, 0, 6); // more efficient than 2 draw calls
  glBindVertexArray(0); //unbind
}




C2TriangleModel::~C2TriangleModel()
{
  //placeholder
}

void CScene::render()
{
  for (auto &m : models)
  {
    m->render();
  }
}
