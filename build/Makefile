.PHONY: all windows mac linux

all: windows mac linux

windows:
	g++ ../sandbox/launcher/launcher.cpp -o buildW/main.exe -O2 -Wall -Wno-missing-braces -Wno-enum-compare -I ../include/ -L ../lib/libW/ -lraylib -lopengl32 -lgdi32 -lwinmm -llua -lbox2d -I ../engine/ -I ../include/lua/ -I ../include/box2d/

mac:
	clang++ -mmacosx-version-min=11.0 -std=c++17 -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL ../lib/libM/libraylib.a ../lib/libM/libbox2d.a ../lib/libM/liblua.a ../sandbox/launcher/launcher.cpp -o main -I ../include/ -I ../include/box2d -I ../include/lua -L ../lib/libM -lraylib -lbox2d -llua

linux:
	g++ ../sandbox/launcher/launcher.cpp -o main -O2 -Wall -Wno-missing-braces -Wno-enum-compare -I ../include/ -L ../lib/libL -lraylib -I ../include/box2d/ -lbox2d -I ../include/lua/ -llua
