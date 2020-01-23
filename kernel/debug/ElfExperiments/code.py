f1 = open("right", "rb")
f2 = open("wrong", "rb")
def xor_strings(xs, ys):
    return "".join(chr(ord(x) ^ ord(y)) for x, y in zip(xs, ys))

a = f1.read().encode("hex")
b = f2.read().encode("hex")
xored = xor_strings(a, b)#.encode("hex")
print xored
print xored and a , xored and b
