#!/usr/bin/env bash

openssl s_client -connect $1:443 -showcerts </dev/zero
