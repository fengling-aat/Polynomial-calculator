.PHONY:main main.o judge.o io.o calculate.o expr.o
main:main.o judge.o io.o calculate.o expr.o judge.h expr.h io.h calculate.h
	g++ main.o judge.o io.o calculate.o expr.o judge.h expr.h io.h calculate.h -o main
main.o:main.cpp
	g++ -c main.cpp -o main.o
judge.o:judge.cpp
	g++ -c judge.cpp -o judge.o
io.o:io.cpp
	g++ -c io.cpp -o io.o
calculate.o:calculate.cpp
	g++ -c calculate.cpp -o calculate.o
expr.o:expr.cpp
	g++ -c expr.cpp -o expr.o
