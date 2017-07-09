

def encode_inner(n, enc_range_start, enc_range_end):
    enc = n + 13
    if (enc > ord(enc_range_end)):
        enc = enc - ord(enc_range_end) + ord(enc_range_start) - 1

    return enc


def encode(s):
    new_s = ''
    for c in s:
        n = ord(c)
        if (n >= ord('a') and n <= ord('z')):
            enc = encode_inner(n, 'a', 'z')
            new_s += chr(enc)

        elif (n >= ord('A') and n <= ord('Z')):
            enc = encode_inner(n, 'A', 'Z')
            new_s += chr(enc)

        else:
            new_s += c

    return new_s



