#include <iostream>
#include "engine.h"


int main()
{
  CEngine engine;
  if (!engine.init(800, 600, "Draw Triangle 2"))
    return -1;
  
  engine.run();
  
  return 0;
}


