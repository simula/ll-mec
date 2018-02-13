#!/bin/bash

unset $DOCS

while getopts ":d" option; do
  case "${option}" in
    d)
      DOCS=1
      ;;
  esac
done

if [ -n "$DOCS" ]; then
  echo "Generating API documentation"
  apidoc -i src/ -o ./docs -f ".*\\.cc$" -f ".*\\.h$"
fi

mkdir -p build
cd build
cmake ..
make -j`nproc`
