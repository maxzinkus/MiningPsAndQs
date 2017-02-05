#!/usr/bin/env python3
import sys, requests, base64

def getModulus(key):
    length = int.from_bytes(key[:4], 'big')
    key = key[4+length:]
    length = int.from_bytes(key[:4], 'big')
    key = key[4+length:]
    length = int.from_bytes(key[:4], 'big')
    modulus = key[5:length + 4]
    return ':'.join('{:02X}'.format(x) for x in modulus)

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
    return list(map(lambda x: getModulus(base64.b64decode(x)), keys))

while 1:
    try:
        line = input("")
    except EOFError:
        break
    for key in pullKey(line):
        print(key)
