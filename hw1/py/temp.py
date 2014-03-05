import string

with open("1.4.txt", "r") as message:

    message = message.read().lower()

    alphas = [i for i in string.ascii_lowercase]
    for i in range(26):
        key = alphas[i:]+alphas[:i]
        #print key
        t = string.maketrans(str(alphas), str(key))
        print "[{0}] {1}".format(i, message.translate(t))
