########################################################################################################################
# simplehttpserver build stage
########################################################################################################################

FROM gcc:latest AS build

RUN apt-get update && \
	apt-get install -y build-essential git cmake libgl1-mesa-dev libglfw3-dev libxinerama-dev libxcursor-dev libxi-dev libasound2-dev doxygen

WORKDIR /simplesynth

COPY . .

WORKDIR /simplesynth/build

RUN cmake .. && make 

CMD [ "/bin/bash" ]