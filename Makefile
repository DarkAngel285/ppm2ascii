all: compile run

debug:
	clang --debug ./ppm_to_ascii.c -o ppm_to_ascii.out

compile:
	clang ./ppm_to_ascii.c -o ppm_to_ascii.out

run:
	./ppm_to_ascii.out

clean:
	rm -f ./ppm_to_ascii.out
