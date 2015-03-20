#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Nie podałeś parametrów!"
    exit

elif [ "$1" == '--view' ] || [ "$1" == '-v' ]
then
    touch View/sources/$2.cpp
    touch View/headers/$2.h
    echo "SOURCES += View/sources/$2.cpp" >> KeilPlugin.pro
    echo "HEADERS += View/headers/$2.h" >> KeilPlugin.pro
elif [ "$1" == 'model' ] || [ "$1" == '-m' ]
then
    touch Model/sources/$2.cpp
    touch Model/headers/$2.h
    echo "SOURCES += Model/sources/$2.cpp" >> KeilPlugin.pro
    echo "HEADERS += Model/headers/$2.h" >> KeilPlugin.pro

else
    echo "Nie rozpoznano argumentu wejsciowego"
fi
