TEMPLATE = app
CONFIG += console
CONFIG -= qt

TARGET = ../../bin/test
INCLUDEPATH += D:/lib/SFML/include

SOURCES += \
    src/Shapes.cpp \
    src/Render.cpp \
    src/RectangleShape.cpp \
    src/Math.cpp \
    src/main.cpp \
    src/Physics/World.cpp \
    src/Physics/Rectangle.cpp \
    src/Physics/Entity.cpp \
    src/Graphics/Entity.cpp \
    src/Graphics/PointShape.cpp \
    src/Graphics/RectangleShape.cpp \
    src/Graphics/SegmentShape.cpp \
    src/Graphics/Shape.cpp

OTHER_FILES += build/makifile

HEADERS += \
    src/Vector2.hpp \
    src/Shapes.hpp \
    src/Render.hpp \
    src/RectangleShape.hpp \
    src/Math.hpp \
    src/Physics/World.hpp \
    src/Physics/Rectangle.hpp \
    src/Physics/Entity.hpp \
    src/Graphics/Entity.hpp \
    src/Graphics/PointShape.hpp \
    src/Graphics/RectangleShape.hpp \
    src/Graphics/SegmentShape.hpp \
    src/Graphics/Shape.hpp \
    src/Singleton.hpp
