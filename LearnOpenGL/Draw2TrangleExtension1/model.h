#pragma once
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <vector>

class CModelBase 
{
public:
  virtual bool init() = 0;
  virtual void render() = 0;  
  virtual ~CModelBase();

protected:
  GLuint VAO;
  GLuint VBO;
  GLuint EBO; 
  GLuint shaderProgram;
  std::vector<GLfloat> vertices;

  virtual void setVertices() = 0;
  bool compileShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
  
};

class C2TriangleModel : public CModelBase
{
public:
  C2TriangleModel();
  bool init();
  ~C2TriangleModel();

protected:
  void setVertices();
  bool createShaders();
  void render();

private:
  void prep2Triangles();
  
};

class CScene
{
public:
  std::vector<CModelBase*> models;
  void init();
  void render();

private:
};