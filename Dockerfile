FROM ubuntu:24.04

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
	build-essential \
	cmake \
	x11-apps \
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

RUN apt-get install -y nlohmann-json3-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Créer un répertoire pour SSH
RUN mkdir -p /root/.ssh

# Copier les clés locales dans le conteneur
COPY /home/quentin/.ssh/gitlab_rpi5 /root/.ssh/id_rsa
COPY /home/quentin/.ssh/gitlab_rpi5.pub /root/.ssh/id_rsa.pub

# Fixer les permissions
RUN chmod 600 /root/.ssh/id_rsa

# Optionnel : ajouter un fichier known_hosts pour éviter les prompts interactifs
RUN ssh-keyscan gitlab.com >> /root/.ssh/known_hosts

# Copier le fichier .vimrc dans le répertoire home de l'utilisateur root
COPY .vimrc /root/.vimrc

WORKDIR /app

