import sys
import os
import imp


def append_gae_path():
    if (sys.platform.startswith("darwin")):
        gae = imp.load_source(
            'gae',
            '/usr/local/Caskroom/google-cloud-sdk/latest/google-cloud-sdk/platform/google_appengine/run_tests.py'
        )
    elif (sys.platform.startswith('win32')):
        gae = imp.load_source(
            'gae',
            'c:/program files/google-cloud-sdk/platform/google_appengine/run_tests.py'
        )

    # add gae libs to path
    sys.path.extend(gae.TEST_LIBRARY_PATHS)


def insert_proj_root():
    # to proj root, not needed if using ide which sets CWD to proj root
    sys.path.insert(
        0,
        os.path.dirname(os.path.dirname(
            os.path.dirname(os.path.abspath(__file__))))
    )
