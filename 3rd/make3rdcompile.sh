#########################################################################
# File Name: make3rdcompile.sh
# Author: Thinking
# mail: program_code@sohu.com 
# Created Time: Sun 07 Jan 2018 02:54:11 AM DST
#########################################################################

buildtype="debug"

function makelibyang() {
    cd libyang
    cmake -DCMAKE_INSTALL_PREFIX=/opt/local/ -DCMAKE_INSTALL_LIBDIR=lib -DCMAKE_BUILD_TYPE=debug .
    make -j
    make install
    cd ..
}

function makelibssh1() {
    cd libssh-0.7.5
    cmake -DCMAKE_INSTALL_PREFIX=/opt/local/ -DCMAKE_BUILD_TYPE=debug .
    make -j
    make install
    cd ..
}

function makelibnetconf2() {
    cd libnetconf2
    cmake -DENABLE_TLS=ON -DENABLE_SSH=ON -DCMAKE_INSTALL_PREFIX=/opt/local -DCMAKE_INSTALL_LIBDIR=lib -DCMAKE_BUILD_TYPE=debug .
    make -j
    make install
    cd .. 
}

function setldpath() {
    export LD_LIBRARY_PATH="LD_LIBRARY_PATH:/opt/local/lib"
}

function 3rdcompile() {
    makelibyang
    makelibssh1
    makelibnetconf2


    setldpath
}


echo "start "
3rdcompile

echo "end"


