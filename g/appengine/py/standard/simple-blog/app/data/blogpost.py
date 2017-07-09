from google.appengine.ext import ndb


class Post(ndb.Model):
    subject = ndb.StringProperty(required=True)
    content = ndb.TextProperty(required=True)
    created = ndb.DateTimeProperty(auto_now_add=True)
    user_id = ndb.IntegerProperty(required=True)
