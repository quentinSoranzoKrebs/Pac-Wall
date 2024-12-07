FROM ubuntu:lts

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
	build-essential \
	git \
	libasound2-dev \
	libx11-dev \
	libxrandr-dev \
	libxi-dev \
	libgl1-mesa-dev \
	libglu1-mesa-dev \
	libxcursor-dev \
	libxinerama-dev \
	libwayland-dev \
	libxkbcommon-dev \
	ca-certificates \
	vim \
	curl \
	software-properties-common \
	apt-transport-https wget

RUN git clone --depth 1 https://github.com/raysan5/raylib.git raylib \
	&& cd raylib/src/ \
	&& make PLATFORM=PLATFORM_DESKTOP \
	&& make install

RUN apt-get install -y nlohmann-json3-dev

# Copier le fichier .vimrc dans le répertoire home de l'utilisateur root
COPY .vimrc /root/.vimrc

WORKDIR /app

