all: compile run

debug:
	clang --debug ./png_to_ascii.c -o png_to_ascii.out

compile:
	clang ./png_to_ascii.c -o png_to_ascii.out

run:
	./png_to_ascii.out

clean:
	rm -f ./png_to_ascii.out
