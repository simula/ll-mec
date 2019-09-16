#!/bin/bash
function install_pistache {
    echo "Installing pistache"
    git clone https://github.com/oktal/pistache.git /tmp/pistache
    mkdir -p /tmp/pistache/build
    cd /tmp/pistache/build
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
    make
    sudo make install
    cd -
}

sudo apt update

unset $DOCS

while getopts d option
do
  case "${option}"
  in
    d) DOCS=1;;
  esac
done

if [ -z $DOCS ]; then
  echo "Installing apidocs and its dependencies"
  sudo apt install npm -y
  sudo npm install apidoc -g
fi

sudo apt install libssl-dev libevent-dev cmake git build-essential g++ -y
install_pistache
