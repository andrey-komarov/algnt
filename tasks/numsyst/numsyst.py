from sys import stdin

def code(num):
    if 0 <= num <= 9:
        return str(num)
    return chr(ord('A') + num - 10)

s = stdin.readline()
b1, b2 = tuple(map(int, stdin.readline().split()))
a = int(s, b1)
ans = []
while a:
    ans += code(a % b2)
    a //= b2
print (''.join(ans[::-1]))
