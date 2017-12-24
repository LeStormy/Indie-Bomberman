# @Author: raph
# @Date:   2017-06-11T17:31:54+02:00
# @Last modified by:   raph
# @Last modified time: 2017-06-12T10:42:25+02:00

#!/bin/sh

zsh=`env | grep "^SHELL=" | grep zsh | wc -l`;
bash=`env | grep "^SHELL=" | grep bash | wc -l`;

rm -rf ~/bin/IndieStudio

if [ $zsh -eq 1 ]
then
    sed '/### INDIE/d' $HOME/.zshrc > tmp
fi
if [ $bash -eq 1 ]
then
    sed '/### INDIE/d' $HOME/.bashrc > tmp
fi

words=`cat tmp | wc -l`;
if [ $words -eq 0 ]
then
  rm tmp
else
    if [ $zsh -eq 1 ]
    then
	rm $HOME/.zshrc
	mv tmp $HOME/.zshrc
    fi
    if [ $bash -eq 1 ]
    then
	rm $HOME/.bashrc
	mv tmp $HOME/.bashrc
    fi
fi
rm -rf ~/.local/Indie/
rm -rf indie
rm -rf build

## TODO: get shconf
