import sys
import os
import webapp2
from app.handlers import (BlogHandler, BlogNewPostHandler,
                          BlogPostHandler, BlogSignupHandler, BlogWelcomeNewUserHandler)

app = webapp2.WSGIApplication([
    webapp2.Route(r'/blog', handler=BlogHandler),
    webapp2.Route(r'/blog/signup', handler=BlogSignupHandler),
    webapp2.Route(r'/blog/<post_id:\d+>', handler=BlogPostHandler),
    webapp2.Route(r'/blog/newpost', handler=BlogNewPostHandler),
    webapp2.Route(r'/blog/welcome', handler=BlogWelcomeNewUserHandler)
], debug=True)
