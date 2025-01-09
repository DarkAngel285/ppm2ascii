all: compile run

compile:
	clang ./png_to_ascii.c

run:
	./a.out

clean:
	rm -f ./a.out
