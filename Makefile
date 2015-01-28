

LIBS=-lQt5WebKitWidgets -L/usr/lib/x86_64-linux-gnu -lQt5Quick -lQt5OpenGL -lQt5PrintSupport -lQt5WebKit -lQt5Qml -lQt5Location -lQt5Widgets -lQt5Network -lQt5Positioning -lQt5Sensors -lQt5Gui -lQt5Core -lGL -lpthread -static-libgcc -static-libstdc++
CFLAGS=-std=c++11
CFLAGS+=-I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I. -I/usr/include/qt5 -I/usr/include/qt5/QtWebKitWidgets -I/usr/include/qt5/QtQuick -I/usr/include/qt5/QtOpenGL -I/usr/include/qt5/QtPrintSupport -I/usr/include/qt5/QtWebKit -I/usr/include/qt5/QtQml -I/usr/include/qt5/QtLocation -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtNetwork -I/usr/include/qt5/QtPositioning -I/usr/include/qt5/QtSensors -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -I.

all:
	g++ main.cpp -o facebook-chat  ${LIBS} ${CFLAGS}  -fPIC