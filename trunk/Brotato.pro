TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += \
	src/shapes.cpp \
	src/render.cpp \
	src/main.cpp

OTHER_FILES += build/makifile

HEADERS += \
	src/shapes.hpp \
	src/render.hpp
