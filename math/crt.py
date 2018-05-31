# Chinese Remainder Theorem
import numpy as np

def pot(x, y, mod):
    a = x
    ret = 1

    while(y > 0):
        if(y&1):
            ret = (ret * a)%mod

        a = (a * a)%mod
        y >>= 1

    return ret

# p = p0 * p1 * ... * p(n-1) pi are pairwise relatively prime
# a = a0     (mod p0)
# a = a1     (mod p1) ...
# a = a(n-1) (mod p(n-1))
# find a given pi and ai
# a = sum[0 <= i < n]{ ai * (p/pi) * ((pi/p)**-1)%pi } % p
# O(N * log2(p))
def crt(a, p):
    # a and p are numpy.arrays
    assert(a.size == p.size)
    n = a.size
    _p = 1
    for it in p:
        _p *= it
    res = 0
    for i in range (n):	
        at = a[i] * ((_p/p[i]) * pot(_p/p[i], p[i]-2, p[i]))%_p
        res = (res + at)%_p
    return res

# O(N**2 * log2(p)) but works with bultin types until final calculations
# Define: a = x0 + x1*p0 + x2*p0*p1 + ... + x[n-1]*p0*...*p[n-2]
# So:  a = x0 (mod p0)
#      a = x0 + x1*po (mod p1)
# So:  x0 = a0 (mod p0)
#      x1 = (a1 - x0)*p0**-1 (mod p1)
#      x2 = ((a2 - x0)*p0**-1 - x1)*p1**-1 (mod p2)
def crt2(a, p):
    # a and p are numpy.arrays
    assert(a.size == p.size)
    n = a.size
    x = np.zeros(n)

    for i in range(n):
        x[i] = a[i]
        for j in range(i):
            x[i] = (x[i] - x[j]) * pot(p[j], p[i]-2, p[i])
            x[i] %= p[i]
            if(x[i] < 0):
                x[i] += p[i]

    # This part could need bit integer
    ret = 0
    pp = 1
    _p = 1
    for it in p:
        _p *= it

    for i in range(n):
        ret = (ret + x[i] * pp)%_p
        pp *= p[i]

    return ret
