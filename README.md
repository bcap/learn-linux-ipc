# Linux Inter Process Communication

Simple examples of Linux IPC

All examples are encapsulated on a docker container

* `make build` will build the docker image along with all examples
* `make start` will build and launch the container
* `make shell` will open a shell within the container. Compiled examples are on the `bin/` directory
* `make stop` stops the container

## Suggested order to explore

1. Fork
    1. `fork`
2. Signals
    1. `signal-int`
    2. `signal-child-wait`
    3. `signal-child-ignore` (not working properly as of now, skip)
    4. `signal-child-handle`
3. Pipes
    1. `pipes`
4. FIFOs
    1. `fifo-simple.sh`
    2. `fifo-multiple-writers.sh`
    3. `fifo-multiple-writers-line-buffered.sh`
5. File Locking
    1. `flock.sh`
    2. `flock`
6. Memory Mapped Files
    1. `shmem`
7. Semaphores
    1. `semaphore`
8. Message Queues
    1. `mqueue-sender` + `mqueue-receiver`    
10. Unix Sockets
    1. `unix-socket-fork`
    2. `unix-socket-server` + `unix-socket-client`
