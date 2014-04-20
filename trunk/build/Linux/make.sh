# !/bin/sh

cd .. && make $1 OS_DIR=Linux SFML_LIB_EXTENSION=so BOX2D_LIB_EXTENSION=a RM="rm -f" CREATE_DIR="mkdir -p" 