import webtest
import unittest
import re
import imports
import webapp2
import main


class TestValidator(unittest.TestCase):

    def setUp(self):
        self.app = webtest.TestApp(main.app)

    def test_get(self):
        res = self.app.get('/')

        assert res.status_int == 200
        assert '<form method="post">' in res.body
        form = res.form

        assert form.method == 'post'
        assert form.action == ''
        assert len(form.fields) == 5

    def test_form_submit_success(self):
        appResponse = self.app.get('/')
        form = appResponse.form
        form.set('username', 'foo')
        form.set('password', 'bar')
        form.set('verify', 'bar')
        formRes = form.submit()

        redirectedResponse = formRes.follow()
        assert 'Welcome! foo' in redirectedResponse

    def test_form_submit_failure(self):
        appResponse = self.app.get('/')
        form = appResponse.form
        form.set('username', 'foo')
        form.set('password', 'bar')
        form.set('verify', 'bar2222')
        formRes = form.submit()
        print 'formres.body'
        print formRes.body
        assert re.match(
            r".*(\.password_match_error)\s*\{\s*(display:\s*inline-block;)\s*\}", formRes.body, re.DOTALL)


if __name__ == '__main__':
    unittest.main()
