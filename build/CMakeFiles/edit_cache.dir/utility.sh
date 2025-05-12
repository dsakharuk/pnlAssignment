set -e

cd /home/danie/pnlProject/pnlAssignment/build
/usr/bin/ccmake.exe -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
