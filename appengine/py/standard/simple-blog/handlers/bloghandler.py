from google.appengine.ext import ndb
from basehandler import Handler
from data import Post


class BlogHandler(Handler):

    def get(self):
        """Show 10 latest posts"""
        posts = Post.query().order(Post.created).fetch(10)
        if posts != None and len(posts) > 0:
            self.render('blog.htm', posts=posts)
        else:
            response_content = {'no_post_warning_visibility': 'block'}
            self.render('blog.htm', **response_content)


class BlogPostHandler(Handler):

    def get(self, post_id, *args, **kwargs):
        """Get a specific post through it permalink"""
        # find post
        post = Post.get_by_id(int(post_id))
        if post != None:
            self.render('blog_post.htm', post=post, to_blog_visibility='block')
        else:
            self.write('No blog post with id %s found' % post_id)


class BlogNewPostHandler(Handler):

    def get(self):
        """Show add new post form"""
        self.render('form_newpost.htm')

    def post(self):
        """Create or update a blog post, redirect to post permalink if successful"""
        subject = self.request.get('subject')
        content = self.request.get('content')

        response_content = {'subject': subject, 'content': content}
        if not subject:
            response_content['subject_error_visibility'] = 'inline-block'
            self.render('form_newpost.htm', **response_content)
        elif not content:
            response_content['content_error_visibility'] = 'inline-block'
            self.render('form_newpost.htm', **response_content)
        else:
            # put into database
            k = Post(subject=subject, content=content).put()
            # redirect to display it as a post
            self.redirect('/blog/%d' % k.id())
