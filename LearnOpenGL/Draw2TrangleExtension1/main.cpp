#include <iostream>
#include "engine.h"
#include "model.h"


int main()
{
  CEngine engine;
  if (!engine.init(800, 600, "Draw 2 Triangle extensions"))
    return -1;

  CScene s;
  /*C2TriangleModel model;
  model.init();*/
  CModel m1, m2;
  std::vector<GLfloat> v({
    0.5F, 0.5F, 0.0F,
    1.0F, -0.5F, 0.0F,
    0.2F, -0.5F, 0.0F
  });
  m1.setVertices(v);
  m1.setDrawLoopFuncs(
    [] () {
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  },
    []() {
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
  );

  m2.setVertices(std::vector<GLfloat>({ 
    -0.2F,  -0.5F, 0.0F,
    -0.5F,  0.5F,  0.0F,
    -1.0F,  -0.5F, 0.0F
  }));

  m2.setDrawLoopFuncs(
    []() {
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  },
    []() {
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
  );

  s.models.push_back(&m1);
  s.models.push_back(&m2);
  
  engine.setScene(&s);
  engine.run();
  
  return 0;
}


