all:
	g++-4.9 -fdiagnostics-color=auto -fopenmp mm.cpp -o mm

clean:
	rm -f mm tags
