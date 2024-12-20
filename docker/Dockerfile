
FROM nvcr.io/nvidia/deepstream:7.0-gc-triton-devel

#https://github.com/drogonframework/drogon/wiki/ENG-02-Installation#drogon-installation
RUN apt-get update && apt-get install -y --no-install-recommends \
	locales \
	git \
	gcc \
	g++ \
	cmake \
	libjsoncpp-dev \
	uuid-dev \
	zlib1g-dev \
	openssl \
	libssl-dev && \
	rm -rf /var/lib/apt/lists/*

RUN /opt/nvidia/deepstream/deepstream/user_additional_install.sh

RUN /opt/nvidia/deepstream/deepstream/update_rtpmanager.sh

RUN cd /tmp && \
	git clone -b v1.9.7 https://github.com/drogonframework/drogon && \
	cd drogon && \
	git submodule update --init && \
	mkdir build && \
	cd build && \
	cmake .. && \
	make && make install

RUN mkdir -p /workspace/project/
COPY ./sources /workspace/project/sources

RUN locale-gen en_US.UTF-8  
ENV LANG en_US.UTF-8  
ENV LANGUAGE en_US:en  
ENV LC_ALL en_US.UTF-8
