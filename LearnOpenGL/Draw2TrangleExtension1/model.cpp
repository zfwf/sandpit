#include "model.h"
#include <vector>
#include <iostream>



bool CModelBase::compileShaders(const char* vertexShaderSource, const char* fragmentShaderSource)
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

CModelBase::~CModelBase()
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

}

bool  C2TriangleModel::init()
{
  prep2Triangles();
  if (!createShaders())
    return false;

  return true;
}

void C2TriangleModel::setVertices()
{
  vertices = {
    0.5F,   0.5F,  0.0F,
    1.0F,   -0.5F, 0.0F,
    0.2F,   -0.5F, 0.0F,
    -0.2F,  -0.5F, 0.0F,
    -0.5F,  0.5F,  0.0F,
    -1.0F,  -0.5F, 0.0F
  };

  //vertices = {
  //  // First triangle
  //  -0.9f, -0.5f, 0.0f,  // Left 
  //  -0.0f, -0.5f, 0.0f,  // Right
  //  -0.45f, 0.5f, 0.0f,  // Top 
  //                       // Second triangle
  //                       0.0f, -0.5f, 0.0f,  // Left
  //                       0.9f, -0.5f, 0.0f,  // Right
  //                       0.45f, 0.5f, 0.0f   // Top 
  //};
}

void C2TriangleModel::prep2Triangles()
{
  setVertices();

  glGenVertexArrays(1, &VAO); // 1. gnerate vertex array object
  glBindVertexArray(VAO); // 2. bind vertex array, this will be the array to store the vertex buffers

  glGenBuffers(1, &VBO); // 1. generate vertex buffer object
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // 2. bind to vertex array (if do not gen vertex array above, it will go to an inbuilt one)
  glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW); // 3. copy vertices data to VBO, which now is bound to a vertex array
  //glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArr), verticesArr, GL_STATIC_DRAW);

  // 4. Then set our vertex attributes pointers for the "position" vertex attribute. vertex consist of 3 vertices, starting at 0 position in vertices array. each vertex is 3 float variable, no padding between vertices
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0); // enable the above attribute (which is at postion 0 in attribute array)
  glBindVertexArray(0); // unbind the VAO after setup
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

  /*glDrawArrays(GL_TRIANGLES, 0, 3);
  glDrawArrays(GL_TRIANGLES, 3, 3);*/
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
