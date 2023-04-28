#!/bin/zsh

# The lock file needs to be the same for all processes, so it can be used as a mutex.
# The content of the file itself does not matter.
# For convinience we use the script itself as the lock file
lock_file="$0"

echo $file

seq 5 | while read -r i; do
  echo "launching job $i"
  flock "$lock_file" -c "echo $i start; sleep 1; echo $i done" &
done

echo "all jobs launched"

# wait on all jobs launched above
wait
