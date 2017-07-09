from google.appengine.ext import ndb
from .basehandler import Handler
from ..data import Post, User
from ..helpers import validator, hasher


class BlogHandler(Handler):

    def get(self):
        """Show 10 latest posts"""
        response_content = dict()
        if self.request.cookies.get('user_id') == None:
            response_content['signup_link_visibility'] = 'block'

        posts = Post.query().order(Post.created).fetch(10)
        if posts != None and len(posts) > 0:
            self.render('blog.htm', posts=posts, **response_content)
        else:
            response_content['no_post_warning_visibility'] = 'block'
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


class BlogSignupHandler(Handler):

    def get(self):
        self.render('signupform.htm')

    def post(self):
        username = self.request.get('username')
        pw = self.request.get('password')
        vpw = self.request.get('verify')
        email = self.request.get('email')

        is_valid_inputs = [
            validator.is_valid_username(username),
            validator.is_unique_username(username),
            validator.is_valid_password(pw),
            validator.is_match_password(pw, vpw),
            validator.is_valid_email(email)]

        if reduce(lambda cur, next: (cur and next), is_valid_inputs):
            hash = hasher.make_pw_hash(username, pw)
            user_key = User(username=username, hash=hash).put()  # store in db
            cookie_value = str(user_key.id()) + '|' + \
                hasher.make_pw_hash(username, pw)
            self.response.headers.add_header(
                'Set-Cookie', 'user_id=%s; Path=/' % cookie_value)
            self.redirect('/blog/welcome')
        else:
            response_content = {'username': username, 'email': email}
            if not is_valid_inputs[0] or not is_valid_inputs[1]:
                response_content[
                    'username_format_error_visibility'] = 'inline-block'
            if not is_valid_inputs[2]:
                response_content[
                    'password_format_error_visibility'] = 'inline-block'
            if not is_valid_inputs[3]:
                response_content[
                    'password_match_error_visibility'] = 'inline-block'
            if not is_valid_inputs[4]:
                response_content[
                    'email_format_error_visibility'] = 'inline-block'

            self.render('signupform.htm', **response_content)


class BlogWelcomeNewUserHandler(Handler):

    def get(self):
        cookie_user_id = self.request.cookies.get('user_id')
        user_id = int(cookie_user_id.split('|')[0])
        u = ndb.Key(User, user_id).get()

        if u:
            self.render('welcome.htm', username=u.username)
        else:
            self.write('404')
