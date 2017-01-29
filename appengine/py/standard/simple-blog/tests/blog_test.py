import webtest
import unittest
import datetime
import re

import helper
helper.append_gae_path()
from google.appengine.api import memcache
from google.appengine.ext import ndb
# may need to delete empty __init__.py in
# platform/google_appengine/lib/fancy_urllib if cannot find
# invalidcertificateexception
from google.appengine.ext import testbed

helper.insert_proj_root()
import main
from data import Post


class BaseTestFixture(unittest.TestCase):

    def setUp(self):
        # First, create an instance of the Testbed class.
        self.testbed = testbed.Testbed()
        # Then activate the testbed, which prepares the service stubs for use.
        self.testbed.activate()
        # Next, declare which service stubs you want to use.
        self.testbed.init_datastore_v3_stub()
        self.testbed.init_memcache_stub()
        # Clear ndb's in-context cache between tests.
        # This prevents data from leaking between tests.
        # Alternatively, you could disable caching by
        # using ndb.get_context().set_cache_policy(False)
        ndb.get_context().clear_cache()

        self.app = webtest.TestApp(main.app)

    def tearDown(self):
        self.testbed.deactivate()


class TestBlogReadHandlers(BaseTestFixture):

    def setUp(self):
        super(TestBlogReadHandlers, self).setUp()

        # setup a bunch of post for testing
        self.posts = [
            Post(key=ndb.Key('Post', 1), subject='subject 1', content='content 1',
                 created=datetime.datetime.now()),
            Post(key=ndb.Key('Post', 2), subject='subject 2', content='content 2',
                 created=datetime.datetime.now()),
            Post(key=ndb.Key('Post', 3), subject='subject 3', content='content 3',
                 created=datetime.datetime.now()),
            Post(key=ndb.Key('Post', 4), subject='subject 4', content='content 4',
                 created=datetime.datetime.now()),
            Post(key=ndb.Key('Post', 5), subject='subject 5', content='content 5',
                 created=datetime.datetime.now()),
            Post(key=ndb.Key('Post', 6), subject='subject 6', content='content 6',
                 created=datetime.datetime.now()),
            Post(key=ndb.Key('Post', 7), subject='subject 7', content='content 7',
                 created=datetime.datetime.now()),
            Post(key=ndb.Key('Post', 8), subject='subject 8', content='content 8',
                 created=datetime.datetime.now()),
            Post(key=ndb.Key('Post', 9), subject='subject 9', content='content 9',
                 created=datetime.datetime.now()),
            Post(key=ndb.Key('Post', 10), subject='subject 10', content='content 10',
                 created=datetime.datetime.now()),
        ]

    def test_get_blog_post(self):
        self.list_of_post_keys = ndb.put_multi(self.posts)
        res = self.app.get('/blog/1')

        assert res.status_int == 200
        assert '<h3 class="post-subject">' in res.body
        assert 'subject 1' in res.body
        assert '<pre class="post-content">' in res.body

    def test_get_invalid_blog_post(self):
        res = self.app.get('/blog/50')

        assert res.status_int == 200
        assert 'No blog post with id 50 found' in res.body

    def test_get_blog_has_posts(self):
        self.list_of_post_keys = ndb.put_multi(self.posts)
        res = self.app.get('/blog')

        assert res.status_int == 200
        assert 'subject 1' in res.body
        assert 'content 10' in res.body

    def test_get_blog_no_posts(self):
        res = self.app.get('/blog')

        assert res.status_int == 200
        assert re.match(
            r".*(\.no_post_warning)\s*\{\s*(display:\s*block;)\s*\}", res.body, re.DOTALL)


class TestBlogNewPostHandlers(BaseTestFixture):

    def setUp(self):
        super(TestBlogNewPostHandlers, self).setUp()

    def test_new_post_success(self):
        appResponse = self.app.get('/blog/newpost')
        form = appResponse.form
        form.set('subject', 'foo')
        form.set('content', 'bar')
        formRes = form.submit()

        redirectedResponse = formRes.follow()
        assert '<h3 class="post-subject">foo</h3>' in redirectedResponse.body
        assert '<pre class="post-content">bar</pre>' in redirectedResponse.body

    def test_new_post_no_subject(self):
        appResponse = self.app.get('/blog/newpost')
        form = appResponse.form
        form.set('content', 'bar')
        formRes = form.submit()

        assert re.match(
            r".*(\.subject_error)\s*\{\s*(display:\s*inline-block;)\s*\}", formRes.body, re.DOTALL)

    def test_new_post_no_content(self):
        appResponse = self.app.get('/blog/newpost')
        form = appResponse.form
        form.set('subject', 'foo')
        formRes = form.submit()

        assert re.match(
            r".*(\.content_error)\s*\{\s*(display:\s*inline-block;)\s*\}", formRes.body, re.DOTALL)


if __name__ == '__main__':
    unittest.main()
