TEMPLATE = app
CONFIG += console 
CONFIG += object_with_source
CONFIG -= qt

TARGET = ../../bin/test

SOURCES += \ 
    src/Core/Math.cpp \
    src/main.cpp \
    src/Physics/World.cpp \
    src/Physics/Rectangle.cpp \
    src/Physics/Entity.cpp \
    src/Graphics/SegmentShape.cpp \
    src/Graphics/RectangleShape.cpp \
    src/Graphics/Shape.cpp \
    src/Graphics/PointShape.cpp \
    src/GameObjects/GameObject.cpp \
    src/Graphics/SFMLEntity.cpp \
    src/Graphics/Entity.cpp \
    src/Windows/FixedFramerateWindow.cpp \
    src/GameObjects/DecorBox.cpp \
    src/GameObjects/Box.cpp \
    src/Graphics/_ThickPointShape.cpp \
    src/Graphics/DebugRenderer.cpp \
    src/Core/Logger.cpp

HEADERS += \ 
    src/Core/Vector2.hpp \
    src/Core/Singleton.hpp \
    src/Core/Math.hpp \
    src/Physics/World.hpp \
    src/Physics/Rectangle.hpp \
    src/Physics/Entity.hpp \
    src/Graphics/SegmentShape.hpp \
    src/Graphics.hpp \
    src/Graphics/RectangleShape.hpp \
    src/Graphics/Shape.hpp \
    src/Graphics/PointShape.hpp \
    src/GameObjects/GameObject.hpp \
    src/Graphics/SFMLEntity.hpp \
    src/Graphics/Entity.hpp \
    src/Windows/FixedFramerateWindow.hpp \
    src/GameObjects/DecorBox.hpp \
    src/GameObjects/Box.hpp \
    src/Physics.hpp \
    src/GameObjects.hpp \
    src/Graphics/_ThickPointShape.hpp \
    src/Graphics/DebugRenderer.hpp \
    src/NonInstantiable.hpp \
    src/Core/NonInstantiable.hpp \
    src/Core.hpp \
    src/Core/Logger.hpp

macx: LIBS += $$PWD/lib/OSX/SFML/libsfml-audio.dylib \
    $$PWD/lib/OSX/SFML/libsfml-graphics.dylib \
    $$PWD/lib/OSX/SFML/libsfml-system.dylib \
    $$PWD/lib/OSX/SFML/libsfml-window.dylib \
    $$PWD/lib/OSX/Box2D/libBox2D.a

INCLUDEPATH += $$PWD/include/SFML \
    $$PWD/include/Box2D

DEPENDPATH += $$PWD/include/SFML \
    $$PWD/include/Box2D
