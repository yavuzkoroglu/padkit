#!/bin/bash -i

if ! command -v brew &> /dev/null
then
    echo ""
    echo "Homebrew is NOT installed"
    echo ""
else
    echo ""
    echo "Homebrew is installed"
    echo ""

    brew install gcc llvm

    if ! grep 'alias gcc=gcc-$(ls $(brew --prefix)/opt/ | grep gcc | tail -1 | sed s/gcc@//)' ~/.bashrc &> /dev/null
    then
        echo 'alias gcc=gcc-$(ls $(brew --prefix)/opt/ | grep gcc | tail -1 | sed s/gcc@//)' >> ~/.bashrc
    fi

    if ! grep 'export PATH=$(brew --prefix)/opt/llvm/bin:${PATH}' ~/.bashrc &> /dev/null
    then
        echo 'export PATH=$(brew --prefix)/opt/llvm/bin:${PATH}' >> ~/.bashrc
    fi
fi
