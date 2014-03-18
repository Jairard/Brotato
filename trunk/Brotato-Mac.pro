TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += \
	src/shapes.cpp \
	src/render.cpp \
	src/main.cpp \
    src/rectangleShape.cpp \
    src/Physics/phyWorld.cpp \
    src/Physics/phyEntity.cpp

OTHER_FILES += build/makifile

HEADERS += \
	src/shapes.hpp \
	src/render.hpp \
    src/vector2.hpp \
    src/rectangleShape.hpp \
    src/Physics/phyWorld.hpp \
    src/Physics/phyEntity.hpp
