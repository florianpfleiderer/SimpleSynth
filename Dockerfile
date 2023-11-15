# Dockerfile
#
# Created on Wed Nov 15 2023 by Florian Pfleiderer
#
# Copyright (c) 2023 TU Wien

FROM gcc:latest AS build

# Install necessary tools
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    git

# Install dependencies
RUN apt-get update && \
    apt-get install -y \
    libgl1-mesa-dev \
    libglfw3-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    libasound2-dev \
    doxygen \
    openssh-server \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /simplesynth

COPY . .

WORKDIR /simplesynth/build

RUN cmake .. && make 

WORKDIR /simplesynth

# Configure SSH
# RUN mkdir /var/run/sshd
# RUN echo 'root:password' | chpasswd
# RUN sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

#expose ssh port
# EXPOSE 22

CMD [ "/bin/bash" ]