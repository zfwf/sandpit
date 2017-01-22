import webtest
import unittest
import imports
import datetime

from google.appengine.api import memcache
from google.appengine.ext import ndb
# may need to delete empty __init__.py in
# platform/google_appengine/lib/fancy_urllib if cannot find
# invalidcertificateexception
from google.appengine.ext import testbed

import main
from data import Post


class TestBlogHandlers(unittest.TestCase):

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

        # setup a bunch of post for testing
        posts = [
            Post(title='title 1', content='content 1',
                 created=datetime.datetime.now()),
            Post(title='title 2', content='content 2',
                 created=datetime.datetime.now()),
            Post(title='title 3', content='content 3',
                 created=datetime.datetime.now()),
            Post(title='title 4', content='content 4',
                 created=datetime.datetime.now()),
            Post(title='title 5', content='content 5',
                 created=datetime.datetime.now()),
        ]

        self.list_of_post_keys = ndb.put_multi(posts)
        print ndb.get_multi(self.list_of_post_keys)

    def test_get_blog_post(self):
        k = self.list_of_post_keys[0]
        res = self.app.get('/blog/%d' % k.id())

        assert res.status_int == 200
        assert '<h3 class="post-subject">' in res.body
        assert '<pre class="post-content">' in res.body

    def tearDown(self):
        self.testbed.deactivate()


if __name__ == '__main__':
    unittest.main()
