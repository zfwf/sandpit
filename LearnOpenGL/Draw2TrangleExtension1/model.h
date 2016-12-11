#pragma once
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <vector>

class CModel 
{
public:
  virtual void setVertices(std::vector<GLfloat>& vertices);
  virtual bool setShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
  virtual void setDrawLoopFuncs(void(*draw)());
  virtual void render();
  virtual ~CModel();

protected:
  GLuint VAO;
  GLuint VBO;
  GLuint EBO; 
  GLuint shaderProgram;
  std::vector<GLfloat> vertices;
  
  void(*drawFunc)();

  
  bool compileShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
  
};

class C2TriangleModel : public CModel
{
public:
  C2TriangleModel();
  ~C2TriangleModel();

protected:
  bool createShaders();
  void render();

private:
  void prep2Triangles();
  
};

class CScene
{
public:
  std::vector<CModel*> models;
  void init();
  void render();
  void clear();
  void setClearFunc(void(*clearBufferFunc)());
protected:
  void(*clearBufferFunc)();

private:
};