TEMPLATE = app
CONFIG -= qt
CONFIG += console 
CONFIG += object_with_source

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

# OSX
macx: LIBS += $$PWD/lib/OSX/SFML/libsfml-audio.dylib \
    $$PWD/lib/OSX/SFML/libsfml-graphics.dylib \
    $$PWD/lib/OSX/SFML/libsfml-system.dylib \
    $$PWD/lib/OSX/SFML/libsfml-window.dylib \
    $$PWD/lib/OSX/Box2D/libBox2D.a

# Windows
win32: LIBS += -L$$PWD/lib/Windows/Box2D/ -lBox2D

win32:CONFIG(release, debug|release): LIBS += $$PWD/lib/Windows/SFML/libsfml-audio.a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/Windows/SFML/ -lsfml-audio-d

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/Windows/SFML/ -lsfml-graphics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/Windows/SFML/ -lsfml-graphics-d

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/Windows/SFML/ -lsfml-main
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/Windows/SFML/ -lsfml-main-d

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/Windows/SFML/ -lsfml-system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/Windows/SFML/ -lsfml-system-d

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/Windows/SFML/ -lsfml-window
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/Windows/SFML/ -lsfml-window-d

# Paths
INCLUDEPATH += $$PWD/include/ 

DEPENDPATH += $$PWD/include/
