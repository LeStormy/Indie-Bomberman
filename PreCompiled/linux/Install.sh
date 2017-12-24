# @Author: raph
# @Date:   2017-06-08T17:41:25+02:00
# @Last modified by:   raph
# @Last modified time: 2017-06-12T10:41:42+02:00

#!/bin/sh

zsh=`env | grep "^SHELL" | grep zsh | wc -l`;
bash=`env | grep "^SHELL=" | grep bash | wc -l`;
rm -rf ~/bin/IndieStudio
if [ $zsh -eq 1 ]
then
    echo "export LD_PRELOAD=\".local/Indie/include/libboost_serialization.so .local/Indie/include/libfreetype.so .local/Indie/include/libIrrlicht.so .local/Indie/include/libopenal.so .local/Indie/include/libsfml-audio.so .local/Indie/include/libsfml-system.so .local/Indie/include/libpng.so .local/Indie/include/libz.so\" ### INDIE" >> $HOME/.zshrc
    echo "export PATH=$HOME/bin:/usr/local/bin:$PATH ### INDIE" >> $HOME/.zshrc

    fi
if [ $bash -eq 1 ]
then
    echo "export LD_PRELOAD=\".local/Indie/include/libboost_serialization.so .local/Indie/include/libfreetype.so .local/Indie/include/libIrrlicht.so .local/Indie/include/libopenal.so .local/Indie/include/libsfml-audio.so .local/Indie/include/libsfml-system.so .local/Indie/include/libpng.so .local/Indie/include/libz.so\" ### INDIE" >> $HOME/.bashrc
    echo "export PATH=$HOME/bin:/usr/local/bin:$PATH ### INDIE" >> $HOME/.bashrc
fi
mkdir -p ~/.local/
mkdir -p ~/.local/Indie
cp -r winInc/ ~/.local/Indie/include/
cp -r ../Media/ ~/.local/Indie/
cp -r ../Misc/ ~/.local/Indie/
cp -r bin/* ~/.local/Indie/
mkdir ~/.local/Indie/Misc/Maps
ln ~/.local/Indie/indie ~/bin/IndieStudio
