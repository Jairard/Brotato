TEMPLATE = app
CONFIG += console 
CONFIG += object_with_source
CONFIG -= qt

TRUNK_DIR = ../../..
BIN_DIR = TRUNK_DIR/bin
SRC_DIR = TRUNK_DIR/src

TARGET = BIN_DIR/Brotato

SOURCES +=  \
    ../../../src/PotatoEngine/UnitTests/main.cpp \
    ../../../src/PotatoEngine/UnitTests/libsHelpers_tests.cpp \
    ../../../src/PotatoEngine/UnitTests/math_tests.cpp \
    ../../../src/PotatoEngine/UnitTests/rect_tests.cpp \
    ../../../src/PotatoEngine/UnitTests/pool_tests.cpp \
    ../../../src/PotatoEngine/UnitTests/stainable_tests.cpp

HEADERS +=  \
    ../../../src/PotatoEngine/UnitTests/catch.hpp \

