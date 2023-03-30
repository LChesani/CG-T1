g++ -c -Iinclude src\Editor.cpp
g++ -c -Iinclude src\gl_canvas2d.cpp
g++ -c -Iinclude src\main.cpp

g++ -o teste.exe Editor.o main.o gl_canvas2d.o -m32 -Iinclude -Llib -lopengl32 -lglu32 -lfreeglut
.\teste.exe