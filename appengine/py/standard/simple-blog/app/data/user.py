from google.appengine.ext import ndb


class User(ndb.Model):
    username = ndb.StringProperty(required=True)
    hash = ndb.StringProperty(required=True)
    created = ndb.DateTimeProperty(auto_now_add=True)
