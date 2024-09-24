FROM	debian:stable AS builder

# Install necessary utils and dependencies
RUN		apt-get update && apt-get install -y build-essential libreadline-dev && rm -rf /var/lib/apt/lists/*

WORKDIR	/app

# Makefile buildsystem
COPY	. .

# Build minishell
RUN		./configure.sh
RUN		make
RUN		make clean

# Final stage
FROM	alpine:latest

# Install dependencies (readline and compact libc)
RUN		apk add --no-cache readline libc6-compat

# Copy binary
COPY	--from=builder /app/minishell /usr/bin/minishell

RUN		chmod 755 /usr/bin/minishell

# Register minishell as a standard shell
RUN		echo "/usr/bin/minishell" >> /etc/shells

# Minishell as entry point 
ENTRYPOINT [ "/usr/bin/minishell" ]
