#!/bin/bash

set -e

rm -f /tmp/fifo
mkfifo /tmp/fifo

for word in foo bar; do
  timeout 1 yes $word > /tmp/fifo &
done

cat /tmp/fifo

wait
