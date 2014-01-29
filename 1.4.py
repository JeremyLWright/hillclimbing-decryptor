import string
import pprint
import operator

p = pprint.PrettyPrinter()
def cipher_print(text):
    groups = [text[i:i+5] for i in range(0, len(text), 5)]
    lines = [groups[i:i+5] for i in range(0, len(groups), 5)]
    p.pprint(lines)
    
    


with open("1.4.txt", "r") as f:
    cipher_text = f.read()
    freq = {l: cipher_text.count(l) for l in string.ascii_uppercase}
    freq = sorted(freq.iteritems(), key=operator.itemgetter(1))
    p.pprint(freq)
    cipher_print(cipher_text)
