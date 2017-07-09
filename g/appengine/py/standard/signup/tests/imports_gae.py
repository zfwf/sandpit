import os
import sys

import imp
gae = imp.load_source(
    'gae',
    '/usr/local/Caskroom/google-cloud-sdk/latest/google-cloud-sdk/platform/google_appengine/run_tests.py'
)

# add gae libs to path
sys.path.extend(gae.TEST_LIBRARY_PATHS)