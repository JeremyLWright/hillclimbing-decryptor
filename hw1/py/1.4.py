import string
import pprint
import operator
import sys

swaps = {
'A':'.',
'B':'.',
'C':'.',
'D':'.',
'E':'.',
'F':'.',
'G':'.',
'H':'.',
'I':'h',
'J':'.',
'K':'.',
'L':'.',
'M':'.',
'N':'.',
'O':'.',
'P':'.',
'Q':'.',
'R':'.',
'S':'.',
'T':'.',
'U':'.',
'V':'.',
'W':'.',
'X':'.',
'Y':'.',
'Z':'t',
}
p = pprint.PrettyPrinter()
def cipher_print(text):
    groups = [text[i:i+5] for i in range(0, len(text), 5)]
    lines = [groups[i:i+5] for i in range(0, len(groups), 5)]

    for line in lines:
        for group in line:
            sys.stdout.write("{0}\t".format(group))
        print ""
    


with open("1.4.txt", "r") as f:
    cipher_text = f.read()
    freq = {l: cipher_text.count(l) for l in string.ascii_uppercase}
    freq = sorted(freq.iteritems(), key=operator.itemgetter(1))
    p.pprint(freq)
    #cipher_print(cipher_text)

    t = string.maketrans(str(swaps.keys()), str(swaps.values()))

    cipher_text = cipher_text.translate(t)
    cipher_print(cipher_text)
    
