########################################################################################################################
# simplehttpserver build stage
########################################################################################################################

FROM alpine:3.17.0 AS build

RUN apk update && apk add --no-cache \
    build-base \
    cmake \
    git

WORKDIR /simplesynth-app

COPY include ./include
COPY src ./src 
COPY tests ./tests
COPY save ./save
COPY CMakeLists.txt ./

WORKDIR /simplesynth-app/build

RUN cmake -DCMAKE_BUILD_TYPE=Release .. && make 

CMD ["./SimpleSynth"]

