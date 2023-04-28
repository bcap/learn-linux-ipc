FROM alpine

RUN apk add bash zsh less
RUN apk add build-base

WORKDIR /linux-ipc

COPY src src

RUN mkdir bin

RUN cp src/*.sh bin/

RUN cc src/flock.c -o bin/flock
RUN cc src/fork.c -o bin/fork
RUN cc src/mqueue-receiver.c -o bin/mqueue-receiver
RUN cc src/mqueue-sender.c -o bin/mqueue-sender
RUN cc src/pipes.c -o bin/pipes
RUN cc src/semaphore.c -o bin/semaphore
RUN cc src/shmem.c -o bin/shmem
RUN cc src/signal-child-handle.c -o bin/signal-child-handle
RUN cc src/signal-child-ignore.c -o bin/signal-child-ignore
RUN cc src/signal-child-wait.c -o bin/signal-child-wait
RUN cc src/signal-int.c -o bin/signal-int
RUN cc src/unix-socket-client.c -o bin/unix-socket-client
RUN cc src/unix-socket-fork.c -o bin/unix-socket-fork
RUN cc src/unix-socket-server.c -o bin/unix-socket-server
RUN cc src/yes.c -o bin/yes

COPY .zshrc /root/

ENTRYPOINT [ "/bin/zsh" ]