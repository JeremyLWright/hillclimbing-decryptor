import string
a = 9
b = 5

message = "UqpLdsGpmzaxbabclByjfcbbsfsghbagabbrhcpfu".lower()

def mul_inverse(num):
    return {(i*num)%26:i for i in range(26)}[1]

a1 = mul_inverse(a)

def offset(letter):
    return ord(letter)-ord('a')

def inset(num):
    return chr(num+ord('a'))

def E(x):
    return (a*x + b) % 26

def D(x):
    return a1*(x-b) % 26

#print message
message = [offset(i) for i in message]
#print message
clear = [D(i) for i in message]
clear_text = "".join([inset(i) for i in clear])
print clear_text
#cipher = [E(i) for i in message]
#cipher_text = "".join([inset(i) for i in cipher])
#print cipher_text


