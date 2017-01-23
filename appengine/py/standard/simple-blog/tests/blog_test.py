import webtest
import unittest
import datetime

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
        posts = [
            Post(key=ndb.Key('Post', 1), title='title 1', content='content 1',
                 created=datetime.datetime.now()),
            Post(key=ndb.Key('Post', 2), title='title 2', content='content 2',
                 created=datetime.datetime.now()),
            Post(key=ndb.Key('Post', 3), title='title 3', content='content 3',
                 created=datetime.datetime.now()),
            Post(key=ndb.Key('Post', 4), title='title 4', content='content 4',
                 created=datetime.datetime.now()),
            Post(key=ndb.Key('Post', 5), title='title 5', content='content 5',
                 created=datetime.datetime.now()),
        ]

        self.list_of_post_keys = ndb.put_multi(posts)

    def test_get_blog_post(self):
        res = self.app.get('/blog/1')

        assert res.status_int == 200
        assert '<h3 class="post-subject">' in res.body
        assert 'title 1' in res.body
        assert '<pre class="post-content">' in res.body

    def test_get_invalid_blog_post(self):
        res = self.app.get('/blog/50')

        assert res.status_int == 200
        assert 'No blog post with id 50 found' in res.body


class TestBlogWriteHandlers(BaseTestFixture):

    def setUp(self):
        super(TestBlogWriteHandlers, self).setUp()

    def test_new_post_success(self):
        appResponse = self.app.get('/blog/newpost')
        form = appResponse.form
        form.set('subject', 'foo')
        form.set('content', 'bar')
        formRes = form.submit()

        redirectedResponse = formRes.follow()
        #assert 'Welcome! foo' in redirectedResponse

    def test_new_post_no_subject(self):
        pass

    def test_new_post_no_content(self):
        pass


if __name__ == '__main__':
    unittest.main()
