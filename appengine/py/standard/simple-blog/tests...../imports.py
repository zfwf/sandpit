import sys
import os


# to tests_ root
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

# to proj root
sys.path.insert(
    0,
    os.path.dirname(os.path.dirname(
        os.path.dirname(os.path.abspath(__file__))))
)

import imports_gae