def norm(v):
  return dot(v, v) ** (0.5)

def dot(v, w):
  return sum([v[x] * w[x] for x in xrange(len(v))])

def normalize(v):
  n = norm(v)
  return [x / n for x in v]

def mult(c, v):
  return [c * x for x in v]

def add(v, w):
  return [v[x] + w[x] for x in xrange(len(v))]

def gramschmidt(vecs):
  def project(w, v):
    return mult(dot(w, v), v)

  # List of n zeroes
  n = len(vecs)
  u = [0] * n

  for i in xrange(n):
    w = vecs[i]
    v = w
    for j in xrange(i):
      v = add(v, mult(-1, project(w, u[j])))
    u[i] = normalize(v)
    print("u" + str(i+1) + " = " + str(u[i]))
  return u
