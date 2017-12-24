#!/bin/bash
rm -f Warnings
rm -f DEBUG
./Install.sh 2> DEBUG
for entry in "src"/*
do
    cat DEBUG | grep "$entry" >> Warnings
done
sed -i -e "/^ *from.*$/d" Warnings
rm -f DEBUG
