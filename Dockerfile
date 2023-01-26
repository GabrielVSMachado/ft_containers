FROM ubuntu:20.04

RUN apt-get update && apt-get install -y build-essential clang-12 wget xz-utils

ENV CRITERION_LINK="https://github.com/Snaipe/Criterion/releases/download/v2.4.1/criterion-2.4.1-linux-x86_64.tar.xz"
ENV CRITERION_TAR="criterion-2.4.1-linux-x86_64.tar.xz"
ENV CRITERION_FOLDER="criterion-2.4.1"

RUN wget ${CRITERION_LINK}
RUN tar -xf ${CRITERION_TAR}
RUN mv ${CRITERION_FOLDER}/include/criterion /usr/include/
RUN mv ${CRITERION_FOLDER}/lib/pkgconfig/* /usr/lib/x86_64-linux-gnu/pkgconfig/
RUN mv ${CRITERION_FOLDER}/lib/lib* /usr/lib/
RUN mv /usr/bin/clang++-12 /usr/bin/clang++
RUN rm /usr/bin/c++
RUN ln -sf /usr/bin/clang++ /usr/bin/c++

WORKDIR /ft_containers

COPY . .

ENTRYPOINT ["make", "test"]
