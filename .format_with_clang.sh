#!/bin/bash
#A script to format all source files of the current project.

cd $1

if stat --printf='' src/*.cpp 2>/dev/null
then
    clang-format -i src/*.cpp
fi

if stat --printf='' include/*.h 2>/dev/null
then
    clang-format -i include/*.h
fi

if stat --printf='' tests/*.cpp 2>/dev/null
then
    clang-format -i tests/*.cpp
fi

if stat --printf='' tests/*.h 2>/dev/null
then
    clang-format -i tests/*.cpp
fi

echo "Done."
