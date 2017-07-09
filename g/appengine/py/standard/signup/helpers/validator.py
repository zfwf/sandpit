import re


def is_valid_username(un):
    return re.match('^[a-zA-Z0-9_-]{3,20}$', un) if un else False


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
