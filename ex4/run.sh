#!/usr/bin/bash
make all > /dev/null
if [ $? -ne 0 ]
then
    echo "make failed, run it yourself to see what went wrong"
    exit 1
fi

./digitcompress -c test.txt
./digitcompress -d test.bin

make clean > /dev/null
