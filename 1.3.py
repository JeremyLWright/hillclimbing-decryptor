import string

message = "jxu auo veh rhuqaydw oekh dunj syfxuh yi hywxj kdtuh oekh deiu"

alphas = [i for i in string.ascii_lowercase]
for i in range(26):
    first = alphas[i:]
    second = alphas[:i]
    key = first+second
    #print key
    t = string.maketrans(str(alphas), str(key))
    print "[{0}] {1}".format(i, message.translate(t))
