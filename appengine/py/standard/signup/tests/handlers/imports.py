import sys
import os
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import tests_imports
print 'tests handlers imports'
print sys.path

from handlers import main
from helpers import validator
