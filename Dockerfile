FROM ubuntu:latest

# 비즈니스 시간 업데이트 및 필수 패키지 설치
RUN apt-get update && \
    apt-get install -y \
    gcc \
    make \
    vim \
    build-essential \
	valgrind \
    && apt-get clean

WORKDIR /mnt

CMD [ "bash" ]
