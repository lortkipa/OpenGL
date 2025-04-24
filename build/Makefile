compiler = clang 
sources = $(shell find ../backend -name *.c)
libraries = -lGL -lGLEW -lglfw
bin = bin
endPoints = ../examples

init:
	mkdir -p bin

triangle:
	$(compiler) $(sources) $(libraries) $(endPoints)/triangle/triangle.c -o $(bin)/triangle

quad:
	$(compiler) $(sources) $(libraries) $(endPoints)/quad/quad.c -o $(bin)/quad
