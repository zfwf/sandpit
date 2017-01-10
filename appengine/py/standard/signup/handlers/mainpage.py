import sys
import os
import imp
# validator = imp.load_source(
#     'validator',
#     os.path.join(
#         os.path.dirname(os.path.dirname(__file__)),
#         'helpers/validator.py'
#     )
# )
from basehandler import Handler
from imports import validator


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
