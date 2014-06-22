#
# Makefile for pong
# 'make all' or 'make pong' to compile project
# 

CC = gcc -Wall 

all: pong

pong: pong.c
	$(CC) pong.c alarmlib.c ball.c court.c paddle.c -lcurses -o pong
