import re
import hasher
from ..data.user import User


def is_valid_username(un):
    return re.match('^[a-zA-Z0-9_-]{3,20}$', un) if un else False


def is_unique_username(un):
    ret = False
    if un:
        # get() first, or fetch(limit=x)
        u = User.gql("WHERE username=:1", un).get()
        if not u:
            ret = True

    return ret


def is_valid_password(pw):
    if pw:
        return re.match('^.{3,20}$', pw)

    return False


def is_match_password(pw, vpw):
    return (pw and (pw == vpw))


def is_valid_email(em):
    if not em:
        return True

    return re.match('^[\S]+@[\S]+.[\S]+$', em)


def valid_pw(name, pw, h):
    # Your code here
    salt = h.split(',')[1]
    actual = hasher.make_pw_hash_with_salt(name, pw, salt)
    return h == actual
