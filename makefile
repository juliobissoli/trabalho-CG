all:	trabalhocg

trabalhocg:
	g++ -o trabalhocg *.cpp -Wall -lm -lGL -lGLU -lglut

clean:
	rm -rf *.o trabalhocg
