import argparse
import cStringIO
import logging
import os.path
import random
import sys
import unittest

DIR_PATH = '/usr/local/Caskroom/google-cloud-sdk/latest/google-cloud-sdk/platform/google_appengine'

TEST_LIBRARY_PATHS = [
    DIR_PATH,
    os.path.join(DIR_PATH, 'lib', 'cherrypy'),
    os.path.join(DIR_PATH, 'lib', 'fancy_urllib'),
    os.path.join(DIR_PATH, 'lib', 'yaml-3.10'),
    os.path.join(DIR_PATH, 'lib', 'antlr3'),
    os.path.join(DIR_PATH, 'lib', 'concurrent'),
    os.path.join(DIR_PATH, 'lib', 'ipaddr'),
    os.path.join(DIR_PATH, 'lib', 'jinja2-2.6'),
    os.path.join(DIR_PATH, 'lib', 'webob-1.2.3'),
    os.path.join(DIR_PATH, 'lib', 'webapp2-2.5.1'),
    os.path.join(DIR_PATH, 'lib', 'mox'),
    os.path.join(DIR_PATH, 'lib', 'protorpc-1.0'),
]


def main():
    sys.path.extend(TEST_LIBRARY_PATHS)

    parser = argparse.ArgumentParser(
        description='Run the devappserver2 test suite.')
    parser.add_argument(
        'tests', nargs='*',
        help='The fully qualified names of the tests to run (e.g. '
        'google.appengine.tools.devappserver2.api_server_test). If not given '
        'then the full test suite will be run.')

    args = parser.parse_args()

    loader = unittest.TestLoader()
    if args.tests:
        tests = loader.loadTestsFromNames(args.tests)
    else:
        tests = loader.discover(
            os.path.join(DIR_PATH, 'google/appengine/tools/devappserver2'),
            '*_test.py')

    runner = unittest.TextTestRunner(verbosity=2)
    runner.run(tests)

if __name__ == '__main__':
    main()
