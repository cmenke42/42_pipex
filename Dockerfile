FROM ubuntu:16.04

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install g++ valgrind -y
#RUN apt-get install libreadline6 libreadline6-dev //installs readline if needed
RUN apt-get update && apt-get install make
