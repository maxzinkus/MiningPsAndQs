Mining Your Ps and Qs
=====================

Project info can be found [here](https://docs.google.com/document/d/1GuHHfoL2-UKoKItMrGqrl6GMeRmnmHqdpLYx8YiZaEI/edit)

Reimplementation of [this paper](https://factorable.net/weakkeys12.extended.pdf)

*Authors:* Max Zinkus, Nick Gonella, Jasper Kahn

## Task I
This task is implemented as a demo program in the `TaskI_Intro` directory. `make` it and run it to see the quick demo of GMP functions.

## Task II
Similar to Task I, this is implemented in `gcd.c` and demo'd with `driver` (just run `make` to build it). The demo finds the GCD of 100 and 125.

## Task III
Task III is implemented as a tool that reads in a file of newline separated, decimal integers and finds the GCDs between all possible pairs of values. Running `make` gives you `gmp_gcd`, which can be run against a file to find the GCD.

Modulus 1 shares a GCD with 4:
`7958371467617366824605775912960638834791855716610959117124052267528546374374593198071120059398734032490380767332883052662861580136473938906942059406675053`

## Task IV
An implementation of RSA can be found in `RSA.c`, conforming to the structures outlined in `RSA.h`.

## Task V
The decrypted message was:
```Message here```

## Task VI
Using some python and shell scripting, we pulled a few thousand public keys from GitHub. A user's public key can be found by visiting `https://github.com/<user>.keys`.

Using the program from Task III, it took about 1m 10s to perform pairwise GCD on these keys. We used `time` for our measurements.

We found three keys that all shared a common factor of 3.

## Task VII
Our lack of resources and knowledge led us to pursue threading as our parallelization scheme. Using pthreads and some other optimizations of how we parsed moduluses, we ran pairwise GCD on the GitHub dataset in about 11s. Both tests were performed on 2013 MacBook Pros.
