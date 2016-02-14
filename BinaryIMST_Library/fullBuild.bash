#!/bin/bash

bash toggleLogs.bash
bash build.bash 'debug'
bash memcheck.bash -r './BinaryIMST_Library' -s 'valgrind.supp' -o 'valgrind.log'
bash toggleLogs.bash
