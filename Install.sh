# @Author: raph
# @Date:   2017-06-08T17:41:25+02:00
# @Last modified by:   raph
# @Last modified time: 2017-06-12T10:41:42+02:00

#!/bin/sh

zsh=`env | grep "^SHELL" | grep zsh | wc -l`;
bash=`env | grep "^SHELL=" | grep bash | wc -l`;
rm -rf build
rm -rf ~/bin/IndieStudio
mkdir build
cd build
cmake ..
make -j8
cd ..
if [ $zsh -eq 1 ]
then
    echo "export LD_PRELOAD=\"`pwd`/winInc/libboost_serialization.so `pwd`/winInc/libfreetype.so `pwd`/winInc/libIrrlicht.so `pwd`/winInc/libopenal.so `pwd`/winInc/libsfml-audio.so `pwd`/winInc/libsfml-system.so `pwd`/winInc/libpng.so `pwd`/winInc/libz.so\" ### INDIE" >> $HOME/.zshrc
    echo "export PATH=$HOME/bin:/usr/local/bin:$PATH ### INDIE" >> $HOME/.zshrc

    fi
if [ $bash -eq 1 ]
then
    echo "export LD_PRELOAD=\"`pwd`/winInc/libboost_serialization.so `pwd`/winInc/libfreetype.so `pwd`/winInc/libIrrlicht.so `pwd`/winInc/libopenal.so `pwd`/winInc/libsfml-audio.so `pwd`/winInc/libsfml-system.so `pwd`/winInc/libpng.so `pwd`/winInc/libz.so\" ### INDIE" >> $HOME/.bashrc
    echo "export PATH=$HOME/bin:/usr/local/bin:$PATH ### INDIE" >> $HOME/.bashrc
fi
mkdir -p ~/.local/
mkdir -p ~/.local/Indie
cp -r Media/ ~/.local/Indie/
cp -r Misc/ ~/.local/Indie/
cp -r bin/* ~/.local/Indie/
cp -r indie ~/.local/Indie/
ln ~/.local/Indie/indie ~/bin/IndieStudio
