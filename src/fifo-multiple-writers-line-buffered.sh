#!/bin/bash

set -e

# be sure that we will use our own yes command instead of the OS one
PATH=$(dirname $0):$PATH

rm -f /tmp/fifo
mkfifo /tmp/fifo

for word in foo bar; do
  timeout 1 yes $word > /tmp/fifo &
done

cat /tmp/fifo

wait
