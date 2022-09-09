#!/bin/bash
loops=100
while ((loops > 0))
do
    build/Release/pala
    echo $loops "=>" $?
    ((loops--))
done
