CC = gcc
CXX = g++
NVCC = nvcc

CFLAGS = -Wall -O2
CXXFLAGS = -Wall -O2 -std=c++11
NVCCFLAGS = -O2

all: mandelbrot_set_c mandelbrot_set_cpp mandelbrot_set_cuda

mandelbrot_set_c: mandelbrot-set.c
	$(CC) $(CFLAGS) -o $@ $< -lm

mandelbrot_set_cpp: mandelbrot-set.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

mandelbrot_set_cuda: mandelbrot-set.cu
	$(NVCC) $(NVCCFLAGS) -o $@ $<

run: all
	@echo -n "Running mandelbrot_set_c:\n"
	@/usr/bin/time -f "real %e\nuser %U\n%P" ./mandelbrot_set_c
	@echo -n "\nRunning mandelbrot_set_cpp:\n"
	@/usr/bin/time -f "real %e\nuser %U\n%P" ./mandelbrot_set_cpp
	@echo -n "\nRunning mandelbrot_set_cuda:\n"
	@/usr/bin/time -f "real %e\nuser %U\n%P" ./mandelbrot_set_cuda

clean:
	rm -f mandelbrot_set_c mandelbrot_set_cpp mandelbrot_set_cuda *.ppm

