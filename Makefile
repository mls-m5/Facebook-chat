

LIBS=-lQt5WebKitWidgets -L/usr/lib/x86_64-linux-gnu -lQt5Quick -lQt5OpenGL -lQt5PrintSupport -lQt5WebKit -lQt5Qml -lQt5Widgets -lQt5Network -lQt5Gui -lQt5Core -lGL -lpthread -static-libgcc -static-libstdc++
CFLAGS=-std=c++11 -g
CFLAGS+=`pkg-config --cflags Qt5WebKit Qt5Gui` -I.

all:
	g++ main.cpp -o facebook-chat  ${LIBS} ${CFLAGS}  -fPIC
