import webtest
import unittest
from imports import main


class TestValidator(unittest.TestCase):

    def test_get(self):
        app = webtest.TestApp(main.app)

        response = app.get('/')

        assert response.status_int == 200
        assert response.body == 'Hello, World!'


if __name__ == '__main__':
    unittest.main()
