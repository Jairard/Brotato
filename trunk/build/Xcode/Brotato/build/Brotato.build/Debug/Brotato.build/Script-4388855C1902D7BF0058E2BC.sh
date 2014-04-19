#!/bin/sh
if [ -e "../../../bin/${TARGET_NAME}.app" ]; then
	rm -R ../../../bin/${TARGET_NAME}.app
fi

mv ${TARGET_BUILD_DIR}/${TARGET_NAME}.app ../../../bin/
