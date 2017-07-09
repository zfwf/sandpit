import random
import string
import hashlib


def make_salt():
    return ''.join(random.choice(string.letters) for x in xrange(5))

# Implement the function valid_pw() that returns True if a user's password
# matches its hash. You will need to modify make_pw_hash.


def make_pw_hash_with_salt(name, pw, salt):
    h = hashlib.sha256(name + pw + salt).hexdigest()
    return '%s|%s' % (h, salt)


def make_pw_hash(name, pw):
    s = make_salt()
    return make_pw_hash_with_salt(name, pw, s)
