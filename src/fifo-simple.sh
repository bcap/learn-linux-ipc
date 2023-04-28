#!/bin/zsh

set -e

rm -f /tmp/fifo
mkfifo /tmp/fifo

echo hello > /tmp/fifo &

cat /tmp/fifo

wait
