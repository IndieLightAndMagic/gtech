#!/bin/bash

echo "SHDR Source Compilation......"

rm -Rf buildout
mkdir buildout

g++ -c shdr.cpp  	-o buildout/shdr.o  	-I../../inc
g++ -c prgrm.cpp 	-o buildout/prgrm.o		-I../../inc
g++ -c shdr.cpp  	-o buildout/shdr.o  	-I../../inc
g++ -c shdr_src.cpp	-o buildout/shdr_src.o	-I../../inc

ar rcs buildout/libshdr.a buildout/shdr.o buildout/prgrm.o buildout/shdr.o buildout/shdr_src.o
