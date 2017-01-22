from google.appengine.ext import ndb
from basehandler import Handler
from data import Post


class BlogHandler(Handler):

    def get(self):
        """Show 10 latest posts"""
        self.write('reply from get BlogHandler')


class BlogPostHandler(Handler):

    def get(self, post_id, *args, **kwargs):
        """Get a specific post through it permalink"""

        self.write('reply from get BlogPostHandler %s' % post_id)
        # find post
        # post = Post.get_by_id(post_id)
        # if post != None:
        #     self.render('blog_post.htm', post=post)


class BlogNewPostHandler(Handler):

    def get(self):
        """Show add new post form"""
        self.write('reply from get BlogNewPostHandler')

    def post(self):
        """Create or update a blog post, redirect to post permalink if successful"""
        self.write('reply from post BlogNewPostHandler')
