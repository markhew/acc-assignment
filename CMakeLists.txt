cmake_minimum_required(VERSION 3.3)
project(ACC_Assignment2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    acc.h
    asgnServer.c
    assgnServer2.c
    error.c
    host_serv.c
    mnc_client.c
    mncclithread.c
    pass_arg1.c
    readline.c
    readlinethread.c
    str_chat.c
    str_echo.c
    strclithread.c
    tcp_connect.c
    tcp_listen.c
    tcpcli02.c
    tcpserv01.c
    tcpserv02.c
    web03.c
    wraplib.c
    wrappthread.c
    wrapsock.c
    wrapstdio.c
    wrapunix.c
    writen.c)

add_executable(ACC_Assignment2 ${SOURCE_FILES})