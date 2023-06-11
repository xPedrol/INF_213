cmake_minimum_required(VERSION 3.25)
project(pratica10)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(pratica10
        driver.cpp
        Mediana.cpp
        MedianaLenta.cpp
        MedianaLenta.h
        MyPriorityQueue.h
        MyQueue.h
        MyStack.h
        MyVecNewIterator.h
#        resolveFila.cpp
#        resolveLabirinto.cpp
        )
