g++ -c -Iinclude src\Nagono.cpp
g++ -c -Iinclude src\TextBox.cpp
g++ -c -Iinclude src\Botao.cpp
g++ -c -Iinclude src\Controlador.cpp
g++ -c -Iinclude src\Editor.cpp
g++ -c -Iinclude src\gl_canvas2d.cpp
g++ -c -Iinclude src\main.cpp
del texte.exe
g++ -o teste.exe Nagono.o Controlador.o Botao.o TextBox.o Editor.o main.o gl_canvas2d.o -m32 -Iinclude -Llib -lopengl32 -lglu32 -lfreeglut
.\teste.exe