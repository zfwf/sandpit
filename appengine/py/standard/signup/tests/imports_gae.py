import os
import sys

# to proj root
sys.path.insert(0, os.path.dirname(
    os.path.dirname(os.path.abspath(__file__))))

import imp
gae = imp.load_source(
    'gae',
    '/usr/local/Caskroom/google-cloud-sdk/latest/google-cloud-sdk/platform/google_appengine/run_tests.py'
)

# add gae libs to path
sys.path.extend(gae.TEST_LIBRARY_PATHS)
print 'import_gae'
#print sys.path
