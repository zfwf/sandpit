#include <iostream>
#include "engine.h"
#include "model.h"


int main()
{
  CEngine engine;
  if (!engine.init(800, 600, "Draw 2 Triangle extensions"))
    return -1;

  CScene s;
  C2TriangleModel model;
  model.init();
  s.models.push_back(&model);
  
  engine.setScene(&s);
  engine.run();
  
  return 0;
}


