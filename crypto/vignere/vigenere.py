def toBase26(char):
  val = ord(char)
  if (val < ord('a') or val > ord('z')):
    return char
  return ord(char) - ord('a')

def toCharacter(num):
  return chr(num + ord('a'))

class VigenereCipher:
  def __init__(self, key):
    self.key = [toBase26(char) for char in key]
    self.period = len(key)
  def encrypt(self, string):
    chars = [toBase26(char) for char in string]
    nums = [(chars[i] + self.key[i % self.period]) % 26 for i in range(len(chars))]
    result = [toCharacter(num) for num in nums]
    return ''.join(result)
  def decrypt(self, string):
    chars = [toBase26(char) for char in string]
    nums = [(chars[i] - self.key[i % self.period]) % 26 for i in range(len(chars))]
    result = [toCharacter(num) for num in nums]
    return ''.join(result)

def slice(l, n):
  for i in xrange(n):
    yield l[i::n]

def toBase3(char):
  return ord(char) - ord("A")

def toCharacter(num):
  return chr(num + ord("A"))

def mostAs(n, ct, template):
  for k0 in range(n):
    key = [(k0 + num) % 3 for num in template]
    ct_b3 = [toBase3(char) for char in ct]
    pt_b3 = [(ct_b3[i] - key[i % 8]) % 3 for i in range(len(ct_b3))]
    As = 0
    for num in pt_b3:
      if (num == 0):
        As = As + 1
    print("k0=" + str(k0) + " has " + str(As) + " As")

def mostBs(n, ct, template):
  for k0 in range(n):
    key = [(k0 + num) % 3 for num in template]
    ct_b3 = [toBase3(char) for char in ct]
    pt_b3 = [(ct_b3[i] - key[i % 8]) % 3 for i in range(len(ct_b3))]
    Bs = 0
    for num in pt_b3:
      if (num == 1):
        Bs = Bs + 1
    print("k0=" + str(k0) + " has " + str(Bs) + " Bs")

def I(l1, l2):
  ttl = 0.0
  for i in range(len(l1)):
    if (l1[i] == l2[i]):
      ttl = ttl + 1
  return ttl

def keyDifference(n, s1, s2):
  for shift in range(n):
    s1_b3 = [toBase3(char) for char in s1]
    s1_shifted_b3 = [(num + shift) % 3 for num in s1_b3]
    s1_shifted = [toCharacter(char) for char in s1_shifted_b3]
    i = I(s1_shifted, s2) / len(s1)
    print("Shift: " + str(shift) + ", I: " + str(i))

def xgramAttack(x, ct):
  maxXgramIndices = []
  for i in range(len(ct) - (x - 1)):
    xgram = ct[i:i+x]
    indices = [i]
    for j in range(i + 1, len(ct) - (x-1)):
      if (ct[j:j+x] == xgram):
        indices.append(j)
    if (len(indices) > len(maxXgramIndices)):
      maxXgramIndices = indices
      maxXgram = xgram
  print("Max " + str(x) + "gram: " + str(maxXgram))
  print("Occurred at " + str(maxXgramIndices))
