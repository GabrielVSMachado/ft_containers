FROM ubuntu:20.04

RUN apt-get update && apt-get install -y build-essential clang-12

RUN mv /usr/bin/clang++-12 /usr/bin/clang++
RUN rm /usr/bin/c++
RUN ln -sf /usr/bin/clang++ /usr/bin/c++

WORKDIR /ft_containers

COPY . .

CMD ["make", "test"]
