#!/bin/bash

bash build.bash 'debug'
bash memcheck.bash -r './BinaryIMST_Example' -s 'valgrind.supp' -o 'valgrind.log'
