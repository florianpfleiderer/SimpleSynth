########################################################################################################################
# simplehttpserver build stage
########################################################################################################################

FROM ubuntu:20.04 as build

RUN apt-get update && \
	apt-get install -y build-essential git cmake

WORKDIR /simplesynth-app

COPY include ./include
COPY src ./src 
COPY tests ./tests
COPY save ./save
COPY CMakeLists.txt ./

WORKDIR /simplesynth-app/build

RUN cmake .. && make 

CMD ["./SimpleSynth"]

