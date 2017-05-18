#!/bin/bash

echo "SHDR Source Compilation......"

rm -Rf buildout
mkdir buildout

g++ -c shdr.cpp  -o out/shdr.o  
g++ -c prgrm.cpp -o out/prgrm.o
g++ -c shdr.cpp  -o out/shdr.o  
g++ -c shdr_src.cpp -o out/shdr_src.o


