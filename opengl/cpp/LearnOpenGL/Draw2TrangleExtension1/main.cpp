#include <iostream>
#include "engine.h"
#include "model.h"


int main()
{
  CEngine engine;
  if (!engine.init(800, 600, "Draw 2 Triangle extensions"))
    return -1;

  CScene s;

  // TODO: use command line input to decide which bits to draw
  /*C2TriangleModel model;
  model.init();*/

  CModel m1, m2;


  m1.setVertices(std::vector<GLfloat> ({
    0.5F, 0.5F, 0.0F,
    1.0F, -0.5F, 0.0F,
    0.2F, -0.5F, 0.0F
  }));

  auto drawFunc = []() {
    glDrawArrays(GL_TRIANGLES, 0, 3);
  };

  m1.setDrawLoopFuncs(drawFunc);

  m2.setVertices(std::vector<GLfloat> ({ 
    -0.2F,  -0.5F, 0.0F,
    -0.5F,  0.5F,  0.0F,
    -1.0F,  -0.5F, 0.0F
  }));

  m2.setDrawLoopFuncs(drawFunc);

  GLchar* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";

  GLchar* fragmentShaderSource1 =
    "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

  GLchar* fragmentShaderSource2 =
    "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
    "}\n\0";

  m1.setShaders(vertexShaderSource, fragmentShaderSource1);
  m2.setShaders(vertexShaderSource, fragmentShaderSource2);

  s.models.push_back(&m1);
  s.models.push_back(&m2);
  s.setClearFunc(
    []() {
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  });

  engine.setScene(&s);
  engine.run();
  
  return 0;
}


