#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

function generateDoc {
  if [ -f Doxyfile ]; then
    doxygen Doxyfile
    make -C ./doc/latex
    mv ./doc/latex/refman.pdf ./doc/documentation.pdf
    rm -rf ./doc/latex
    rm -rf ./doc/html
    echo -e "${GREEN}Documentation generated${NC}"
  else
    echo -e "${RED}Doxyfile not found${NC}"
    echo -e "${RED}Please, run the script from the project root directory${NC}"
    exit 1
  fi
}

generateDoc