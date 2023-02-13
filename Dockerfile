FROM ubuntu:20.04

RUN apt-get update

RUN DEBIAN_FRONTEND=noninteractive\
    TZ=America/Sao_Paulo \
    apt-get install -y tzdata build-essential clang-12 valgrind

RUN mv /usr/bin/clang++-12 /usr/bin/clang++
RUN rm /usr/bin/c++
RUN ln -sf /usr/bin/clang++ /usr/bin/c++

WORKDIR /ft_containers

COPY . .

CMD ["make", "test"]
