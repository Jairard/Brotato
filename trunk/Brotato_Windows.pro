TEMPLATE = app
CONFIG += console
CONFIG -= qt

TARGET = ../../bin/test

SOURCES += \
	src/shapes.cpp \
	src/render.cpp \
	src/main.cpp \
    src/rectangleShape.cpp \
    src/Physics/phyWorld.cpp

OTHER_FILES += build/makifile

HEADERS += \
	src/shapes.hpp \
	src/render.hpp \
    src/rectangleShape.hpp \
    src/vector2.hpp \
    src/Physics/phyWorld.hpp
