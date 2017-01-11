import sys
import os

print 'main.py'
print sys.path

from handlers import MainPage, WelcomePage
import webapp2


app = webapp2.WSGIApplication([
    ('/', MainPage),
    ('/welcome', WelcomePage)
], debug=True)
