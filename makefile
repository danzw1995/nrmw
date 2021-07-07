nrmw.exe: main.cpp libdynfunc.dll
	g++ main.cpp libdynfunc.dll -o nrmw

libdynfunc.dll: lib/func/func.cpp
	g++ ./lib/func/func.cpp -I ./lib/func  -fPIC -shared -o libdynfunc.dll
