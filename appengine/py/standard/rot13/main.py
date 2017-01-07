import os
import jinja2
import webapp2
import encoderot13

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


class MainPage(Handler):

    def get(self):
        self.render('rot13_textarea.htm')

    def post(self):
        rot13 = self.request.get('text')
        encoded = encoderot13.encode(rot13)
        self.render('rot13_textarea.htm', rot13=encoded)


app = webapp2.WSGIApplication([
    ('/', MainPage),
], debug=True)
