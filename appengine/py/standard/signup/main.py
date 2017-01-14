import sys
import os
import webapp2
from handlers import MainPage, WelcomePage

app = webapp2.WSGIApplication([
    ('/', MainPage),
    ('/welcome', WelcomePage)
], debug=True)
