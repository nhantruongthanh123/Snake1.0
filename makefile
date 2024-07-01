all: compile link

compile:
	g++ -c snake1.0.cpp -I"D:\SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.1\include" 

link:
	g++ snake1.0.o -o snake1.0 -L "D:\SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.1\lib" -lsfml-graphics -lsfml-window -lsfml-system
	.\snake1.0

