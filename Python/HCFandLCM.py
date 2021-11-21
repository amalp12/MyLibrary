from math import gcd

def get_hcf(arr):
    hcf = arr[0] 
    for i in arr:
        hcf = gcd(hcf,i)
    return hcf

def lcm(a,b):
    return a*b//gcd(a,b)

def get_lcm(arr):
    l = arr[0] 
    for i in arr:
        l = lcm(l,i)
    return l
