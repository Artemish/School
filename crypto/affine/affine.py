import itertools
from utils import binary_search, is_english_word

def modularInverse(c, mod):
  for i in range(1, mod):
    if ((c * i) % mod == 1):
      return i;
  raise Exception("Constant 'a' has no modular inverse.")

def toBase26(char):
  val = ord(char)
  if (val < ord('a') or val > ord('z')):
    raise Exception("Invalid character detected.")
  return ord(char) - ord('a')

def toCharacter(num):
  return chr(num + ord('a'))

class AffineCipher:
  def __init__(self, a, b, mod=26):
    self.a = a
    self.b = b
    self.a_1 = modularInverse(a, mod)
    self.mod = mod
  def encrypt_char(self, char):
    try:
      return toCharacter((toBase26(char) * self.a + self.b) % self.mod)
    except Exception:
        return char
  def decrypt_char(self, char):
    try:
      return toCharacter(((toBase26(char) - self.b) * self.a_1) % self.mod)
    except Exception:
      return char
  def encrypt(self, string):
    chars = [self.encrypt_char(char) for char in string];
    return ''.join(chars)
  def decrypt(self, string):
    chars = [self.decrypt_char(char) for char in string];
    return ''.join(chars)
    
def most_english_words(ciphers, ciphertext):
  def num_words(cipher):
    plaintext = cipher.decrypt(ciphertext)
    words = 0
    for word in plaintext.split():
      if is_english_word(word):
        words = words + 1
    return words
  max_words = -1
  wordiest = None
  for cipher in ciphers:
    words = num_words(cipher)
    if words > max_words:
      max_words = words
      wordiest = cipher
  return wordiest

def make_ciphers():
  a_candidates = [1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25]
  b_candidates = range(0, 26)
  tuples = list(itertools.product(a_candidates, b_candidates))
  return [AffineCipher(a, b) for (a, b) in tuples]

def crack_affine(ciphertext):
  ciphers = make_ciphers()
  best = most_english_words(ciphers, ciphertext)
  print("Best match: " + best.decrypt(ciphertext))
  print("With cipher: f(t) = " + str(best.a) + "t + " + str(best.b))
  print("With inverse: g(t) = " + str(best.a_1) + "*(t - " + str(best.b) + ")")
