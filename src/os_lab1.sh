#!/bin/bash

if [[ "$1" != "" ]]; then
    dirpath="$1"
else
    dirpath=.
fi

echo "Hi, $USER!"
echo "Directory $dirpath"

for dir in "$dirpath"/*
do
    if [[ -d $dir ]]; then
        echo "<DIR> ${dir##*/}"
    fi
done

for file in "$dirpath"/*
do
    if [[ -f $file ]]; then
        printf "${file##*/} "
        stat -c '| %s | %y | %h' $file
    fi
done
