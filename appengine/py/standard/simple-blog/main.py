import sys
import os
import webapp2
from handlers import BlogHandler, BlogPostHandler, BlogNewPostHandler

app = webapp2.WSGIApplication([
    webapp2.Route(r'/blog', handler=BlogHandler),
    webapp2.Route(r'/blog/<post_id:\d+>', handler=BlogPostHandler),
    webapp2.Route(r'/blog/newpost', handler=BlogNewPostHandler)
], debug=True)
