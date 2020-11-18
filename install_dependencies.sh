#!/bin/bash
install_pistache() {
    pushd $LLMEC_DIR/build/ext
    echo "Installing pistache"
    git clone https://github.com/oktal/pistache.git
    cd pistache || exit
    git checkout 2ef937c434810858e05d446e97acbdd6cc1a5a36
    mkdir build
    cd build
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
    make
    sudo make install
    popd
}

install_nlohmann() {
    pushd $LLMEC_DIR/build/ext
    echo "Installing Nlohmann Json"
    git clone https://github.com/nlohmann/json.git
    cd json && git checkout master
    git submodule update --init
    mkdir build
    cd build
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DJSON_BuildTests=OFF ..
    make
    sudo make install
    popd
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

LLMEC_DIR="$(pwd)"
mkdir -p build/ext
install_pistache
install_nlohmann
