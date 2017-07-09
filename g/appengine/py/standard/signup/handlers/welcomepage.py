from basehandler import Handler


class WelcomePage(Handler):

    def get(self):
        username = self.request.get('username')
        self.render('welcome.htm', username=username)
