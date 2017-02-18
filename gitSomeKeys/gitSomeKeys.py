#!/usr/bin/env python3
import sys, requests, base64

def filterRSA(keys):
    key_material = []
    for key in keys:
        key_parts = key.split(' ')
        if len(key_parts) == 2 and "ssh-rsa" == key_parts[0]:
            key_material.append(key_parts[1])
    return key_material

def pullKey(addr):
    key_lines = requests.get(addr + ".keys").text.split('\n')
    keys = filterRSA(key_lines)
    return keys

from subprocess import getoutput, call

def convert(path):
    call("ssh-keygen -f %s -e -m PEM > tmp.pem" % path, shell=True)
    with open('tmp.pem', 'r') as f:
        lns = f.readlines()
    strip = filter(lambda u: "PUBLIC KEY" not in u, lns)
    joined = ''.join(strip)
    with open("tmp.der", "w") as o:
        o.write(joined)
    out = getoutput("cat tmp.der | base64 -d | openssl asn1parse -inform DER") 
    call("rm ./tmp.der ./tmp.pem", shell=True)
    return out.split()[out.split().index("INTEGER")+1][1:]
