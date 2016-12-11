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


