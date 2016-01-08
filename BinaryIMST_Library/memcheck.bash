#!/bin/bash

echo -e "
Running valgrind (log file will be generated as '$2')...";
valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --show-reachable=yes --log-file=$2 --gen-suppressions=all -v ./$1
#
definitely_leak=$(cat "$2" | grep "definitely lost:" | tail -1 | perl -pe 's|.*: ([0-9,]+).*|\1|')
indirectly_leak=$(cat "$2" | grep "indirectly lost:" | tail -1 | perl -pe 's|.*: ([0-9,]+).*|\1|')
possibly_leak=$(cat "$2" | grep "possibly lost:" | tail -1 | perl -pe 's|.*: ([0-9,]+).*|\1|')
reachable_leak=$(cat "$2" | grep "still reachable:" | tail -1 | perl -pe 's|.*: ([0-9,]+).*|\1|')
suppressed_leak=$(cat "$2" | grep "suppressed" | tail -1 | perl -pe 's|.*: ([0-9,]+).*|\1|')
errors=$(cat "$2" | grep "ERROR SUMMARY" | tail -1 | perl -pe 's|.*ERROR SUMMARY: ([0-9,]+).*|\1|')
suppressed=$(cat "$2" | grep "ERROR SUMMARY" | tail -1 | perl -pe 's|.*suppressed: ([0-9,]+).*|\1|')

if [ "$definitely_leak" != "0" ]; then
	echo -e "\nSomething goes wrong: $definitely_leak are definitely lost, see '$2' for details...\n"
fi

if [ "$indirectly_leak" != "0" ]; then
	echo -e "\nSomething goes wrong: $indirectly_leak are indirectly lost, see '$2' for details...\n"
fi

if [ "$possibly_leak" != "0" ]; then
	echo -e "\nSomething goes wrong: $possibly_leak are possibly lost, see '$2' for details...\n"
fi

if [ "$reachable_leak" != "0" ]; then
	echo -e "\nSomething goes wrong: $reachable_leak are still reachable, see '$2' for details...\n"
fi

if [ "$suppressed_leak" != "0" ]; then
	echo -e "\nSomething goes wrong: $reachable_leak are suppressed, see '$2' for details...\n"
fi

if [ "$suppressed" != "0" ]; then
	echo -e "\nSomething goes wrong: there were $suppressed suppressed errors, see '$2' for details...\n"
fi

if [ "$errors" == 0 ]; then
	echo "No errors."
else
	echo -e "\nSomething goes wrong: there were $errors errors, see '$2' for details...\n"
fi
