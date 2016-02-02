#!/bin/bash


# Public function
# Parse command line arguments
#
#	-r --runnable <arg>		path to executable file which will be memchecked
#	-o --output <arg>		path where all valgrind logs will be redirected
#	-s --suppressions <arg>		path to file with additional suppressions for valgrind
#
function pasreBash() {
	while [[ $# > 0 ]]
	do
		case $1 in
			-r|--runnable)
				runnable_path=$(expandFilePath "$2")
				shift # past argument
			;;
			-o|--output)
				output_path=$(expandFilePath "$2")
				shift # past argument
			;;
			-s|--suppressions)
				suppressions_path=$(expandFilePath "$2")
				shift # past argument
			;;
			*)
				printHelp
				exit;
			;;
		esac
		shift # past argument or value
	done
}

# Public function
#
# Print help for script
#
function printHelp() {
	echo "Usage: [sudo] bash memcheck.sh -r|--runnable <arg> [-o|--output <arg>] [-s|--suppressions <arg>]"
	echo "	-r --runnable <arg>		path to executable file which will be memchecked"
	echo "	-o --output <arg>		path where all valgrind logs will be redirected"
	echo "	-s --suppressions <arg>		path to file with additional suppressions for valgrind"
}

# Public function
# Expand special character '~'/'.', if occurred, to home/current directory.
# Only first '~'/'.' will be expanded.
#
function expandFilePath() {
	# Expand of ~ character
	local var="${1/#\~/$HOME}"

	# Expand of . character
	local var="${var/#\./$PWD}"

	echo "$var"
}

# Public function
# Expand special character '~'/'.', if occurred, to home/current directory.
# Only first '~'/'.' will be expanded.
# Add '/' as a last character if needed
#
function expandDirPath() {
	# Expand of ~ character
	local var="$(expandFilePath "$1")"

	# Add '/' as a last character if needed
	if ! [[ "$var" =~ '/'$ ]]; then 
		var=$var'/'
	fi

	echo "$var"
}

function parseSummary() {
	definitely_leak=$(cat "$1" | grep "definitely lost:" | tail -1 | perl -pe 's|.*: ([0-9,]+).*|\1|')
	indirectly_leak=$(cat "$1" | grep "indirectly lost:" | tail -1 | perl -pe 's|.*: ([0-9,]+).*|\1|')
	possibly_leak=$(cat "$1" | grep "possibly lost:" | tail -1 | perl -pe 's|.*: ([0-9,]+).*|\1|')
	reachable_leak=$(cat "$1" | grep "still reachable:" | tail -1 | perl -pe 's|.*: ([0-9,]+).*|\1|')
	suppressed_leak=$(cat "$1" | grep "suppressed" | tail -1 | perl -pe 's|.*: ([0-9,]+).*|\1|')
	errors=$(cat "$1" | grep "ERROR SUMMARY" | tail -1 | perl -pe 's|.*ERROR SUMMARY: ([0-9,]+).*|\1|')
	suppressed=$(cat "$1" | grep "ERROR SUMMARY" | tail -1 | perl -pe 's|.*suppressed: ([0-9,]+).*|\1|')

	if [ "$definitely_leak" != "0" ]; then
		echo -e "\nSomething goes wrong: $definitely_leak are definitely lost, see '$1' for details...\n"
	fi

	if [ "$indirectly_leak" != "0" ]; then
		echo -e "\nSomething goes wrong: $indirectly_leak are indirectly lost, see '$1' for details...\n"
	fi

	if [ "$possibly_leak" != "0" ]; then
		echo -e "\nSomething goes wrong: $possibly_leak are possibly lost, see '$1' for details...\n"
	fi

	if [ "$reachable_leak" != "0" ]; then
		echo -e "\nSomething goes wrong: $reachable_leak are still reachable, see '$1' for details...\n"
	fi

	if [ "$suppressed_leak" != "0" ]; then
		echo -e "\nSomething goes wrong: $reachable_leak are suppressed, see '$1' for details...\n"
	fi

	if [ "$suppressed" != "0" ]; then
		echo -e "\nSomething goes wrong: there were $suppressed suppressed errors, see '$1' for details...\n"
	fi

	if [ "$errors" == 0 ]; then
		echo "No errors."
	else
		echo -e "\nSomething goes wrong: there were $errors errors, see '$1' for details...\n"
	fi
}


#################################################################################################################

pasreBash $@

if [ -z "$runnable_path" ]; then
	printHelp
	exit;
elif [ -n "$output_path" ] && [ -n "$suppressions_path" ]; then
	echo -e "Running valgrind with additional configuration from file '$suppressions_path' (log file will be generated as '$output_path')...";
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --show-reachable=yes --log-file="$output_path" --gen-suppressions=all --suppressions="$suppressions_path" -v "$runnable_path"
	parseSummary "$output_path"
elif [ -n "$output_path" ]; then
	echo -e "Running valgrind (log file will be generated as '$output_path')...";
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --show-reachable=yes --log-file="$output_path" --gen-suppressions=all -v "$runnable_path"
	parseSummary "$output_path"
elif [ -n "$suppressions_path" ]; then
	echo -e "Running valgrind with additional configuration from file '$suppressions_path'...";
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --show-reachable=yes --gen-suppressions=all --suppressions="$suppressions_path" -v "$runnable_path"
else
	echo -e "Running valgrind...";
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --show-reachable=yes --gen-suppressions=all -v "$runnable_path"
fi

