FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update &&\
    apt-get install software-properties-common -y &&\
    add-apt-repository ppa:ubuntu-toolchain-r/test -y &&\
    apt-get install -y \
        g++-10 \
        gcc-10\
        make \
        checkinstall \
        git \
        autoconf \
        libssl1.1 \
        wget \
        ca-certificates \
        ninja-build \
        doxygen \
        doxygen-latex \
        graphviz \
        libxaw7-dev \
        libxrandr-dev \
        libglew-dev \
        libpulse-dev \
        zlib1g-dev \
        libssl-dev \
        libgmp-dev \
        libmpfr-dev \
        libmpc-dev \
        libisl-dev \
        libgmp10 \
        libmpfr6 \
        libmpc3 \
        yasm \
        file \
        patch \
        gperf \
        xz-utils \
        bzip2 \
        zip \
        nsis \
        > /dev/null

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 900 --slave /usr/bin/g++ g++ /usr/bin/g++-10

ENV MINGW=/mingw

ARG BINUTILS_VERSION=2.33.1
ARG MINGW_VERSION=7.0.0
ARG GCC_VERSION=10.1.0
ARG PKG_CONFIG_VERSION=0.29.2

WORKDIR /mnt

RUN wget -q https://pkg-config.freedesktop.org/releases/pkg-config-${PKG_CONFIG_VERSION}.tar.gz -O - | tar -xz
RUN wget -q https://ftpmirror.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.xz -O - | tar -xJ
RUN wget -q https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/mingw-w64-v${MINGW_VERSION}.tar.bz2/download -O - | tar -xj
RUN wget -q https://ftpmirror.gnu.org/gnu/gcc/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.xz -O - | tar -xJ
RUN mkdir -p ${MINGW}/include ${MINGW}/lib/pkgconfig

RUN cd pkg-config-${PKG_CONFIG_VERSION} \
    && ./configure \
       --prefix=/usr \
       --with-pc-path=${MINGW}/lib/pkgconfig \
       --with-internal-glib \
       --disable-shared \
       --disable-nls \
    && make -j`nproc` > /dev/null \
    && make install > /dev/null \
    && cd ..

RUN cd binutils-${BINUTILS_VERSION} \
    && ./configure \
      --prefix=/usr \
      --target=x86_64-w64-mingw32 \
      --disable-shared \
      --enable-static \
      --enable-lto \
      --enable-plugins \
      --disable-multilib \
      --disable-nls \
      --disable-werror \
      --with-system-zlib \
    && make -j`nproc` > /dev/null \
    && make install > /dev/null \
    && cd ..

RUN mkdir mingw-w64 \
    && cd mingw-w64 \
    && ../mingw-w64-v${MINGW_VERSION}/mingw-w64-headers/configure \
      --prefix=/usr/x86_64-w64-mingw32 \
      --host=x86_64-w64-mingw32 \
      --enable-sdk=all \
      --enable-secure-api \
    && make -j`nproc` > /dev/null \
    && make install > /dev/null \
    && cd ..

RUN mkdir gcc \
    && cd gcc \
    && ../gcc-${GCC_VERSION}/configure \
      --prefix=/usr \
      --target=x86_64-w64-mingw32 \
      --enable-languages=c,c++ \
      --disable-shared \
      --enable-static \
      --enable-threads=posix \
      --enable-libgomp \
      --enable-libatomic \
      --enable-graphite \
      --enable-libstdcxx-pch \
      --enable-libstdcxx-debug \
      --disable-multilib \
      --enable-lto \
      --disable-nls \
      --disable-werror \
    && make -j`nproc` all-gcc > /dev/null \
    && make install-gcc > /dev/null \
    && cd ..

RUN cd mingw-w64 \
    && ../mingw-w64-v${MINGW_VERSION}/mingw-w64-crt/configure \
      --prefix=/usr/x86_64-w64-mingw32 \
      --host=x86_64-w64-mingw32 \
      --enable-wildcard \
      --disable-lib32 \
      --enable-lib64 \
    && make -j`nproc` > /dev/null \
    && make install > /dev/null \
    && cd ..

RUN cd mingw-w64 \
    && ../mingw-w64-v${MINGW_VERSION}/mingw-w64-libraries/winpthreads/configure \
      --prefix=/usr/x86_64-w64-mingw32 \
      --host=x86_64-w64-mingw32 \
      --enable-static \
      --disable-shared \
    && make -j`nproc` > /dev/null \
    && make install > /dev/null \
    && cd ..

RUN cd gcc \
    && make -j`nproc` > /dev/null \
    && make install > /dev/null \
    && cd ..

ARG CMAKE_VERSION=3.16.6
ARG CMAKE_HOME=/opt/cmake

RUN wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-Linux-x86_64.sh \
          -q -O /tmp/cmake-install.sh \
          && chmod u+x /tmp/cmake-install.sh \
          && mkdir /opt/cmake \
          && /tmp/cmake-install.sh --skip-license --prefix=${CMAKE_HOME} \
          && rm /tmp/cmake-install.sh
ENV PATH="${CMAKE_HOME}/bin:${PATH}"