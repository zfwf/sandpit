import os
import jinja2
import webapp2
import validator

template_dir = os.path.join(os.path.dirname(__file__), 'templates')
jinja_env = jinja2.Environment(
    loader=jinja2.FileSystemLoader(template_dir), autoescape=True)


class Handler(webapp2.RequestHandler):

    def write(self, *p, **kw):
        self.response.write(*p, **kw)

    def render_str(self, template, **params):
        t = jinja_env.get_template(template)
        return t.render(params)

    def render(self, template, **kw):
        self.write(self.render_str(template, **kw))


class WelcomePage(Handler):

    def get(self):
        username = self.request.get('username')
        self.render('success.htm', username=username)


class MainPage(Handler):

    def get(self):
        self.render('signupform.htm')

    def post(self):
        username = self.request.get('username')
        pw = self.request.get('password')
        vpw = self.request.get('verify')
        email = self.request.get('email')

        is_valid_inputs = [
            validator.is_valid_username(username),
            validator.is_valid_password(pw),
            validator.is_match_password(pw, vpw),
            validator.is_valid_email(email)]

        if reduce(lambda cur, next: (cur and next), is_valid_inputs):
            self.redirect('/welcome?username=%s' % username)
        else:
            response_content = {'username': username, 'email': email}
            if not is_valid_inputs[0]:
                response_content[
                    'username_format_error_visibility'] = 'inline-block'
            if not is_valid_inputs[1]:
                response_content[
                    'password_format_error_visibility'] = 'inline-block'
            if not is_valid_inputs[2]:
                response_content[
                    'password_match_error_visibility'] = 'inline-block'
            if not is_valid_inputs[3]:
                response_content[
                    'email_format_error_visibility'] = 'inline-block'

            self.render('signupform.htm', **response_content)

app = webapp2.WSGIApplication([
    ('/', MainPage),
    ('/welcome', WelcomePage)
], debug=True)
