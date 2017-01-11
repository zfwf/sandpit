import sys
import os
import webtest
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import imports_gae
import webapp2

# to proj root
sys.path.insert(
    0,
    os.path.dirname(os.path.dirname(
        os.path.dirname(os.path.abspath(__file__))))
)

from handlers import MainPage, WelcomePage


class TestValidator(unittest.TestCase):

    def setUp(self):
        self.app = webtest.TestApp(webapp2.WSGIApplication([
            ('/', MainPage),
            ('/welcome', WelcomePage)
        ], debug=True))

    def test_get(self):
        response = self.app.get('/')

        assert response.status_int == 200
        assert response.body == 'Hello, World!'


if __name__ == '__main__':
    unittest.main()
