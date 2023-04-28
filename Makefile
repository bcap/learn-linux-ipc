.DEFAULT_GOAL=build

build:
	docker build -t linux-ipc:latest .

start: build
	docker run -it --rm -d --name linux-ipc linux-ipc:latest
	echo "=> container linux-ipc running, use make shell to run a shell in the container, or make stop to stop it"

stop:
	docker kill linux-ipc

shell:
	docker exec -it linux-ipc /bin/zsh