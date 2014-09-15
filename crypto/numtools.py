def gcd(a, b):
  if (b > a):
    (a, b) = (b, a)
  while True:
    (quotient, remainder) = divmod(a, b)
    print(str(a) + " - " + str(quotient) + "*" + str(b) + " = " + str(remainder))
    a = remainder
    (a, b) = (b, a)
    if (remainder == 0):
      return
  
