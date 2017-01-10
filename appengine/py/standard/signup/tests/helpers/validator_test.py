import unittest
from imports import validator


class TestValidator(unittest.TestCase):

    def test_username_invalidchar(self):
        self.assertFalse(validator.is_valid_username('fgf fefe'))


if __name__ == '__main__':
    unittest.main()
