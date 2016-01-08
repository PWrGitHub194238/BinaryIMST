#!/bin/bash

sharedLibConfigDir='/etc/ld.so.conf.d/'

gTestSharedLibConfigFile='gTest.conf'
gTestGitURL='https://github.com/google/googletest.git'

# Public function
# Parse command line arguments
#
#	-d --defaults			set script not to prompt about any value which has a default one specified
#	-f --force-yes			force every prompt to be skiped with 'y' value - use with caution
#	--gtest-path <arg>		path where GTest project will be downloaded
#	--gtest-lib-path <arg>		path where GTest static library will be moved
#	--gtest-include-path <arg>	path where GTest header files will be moved
#
function pasreBash() {
	while [[ $# > 0 ]]
	do
		case $1 in
			-d|--defaults)
				DEFAULT='y'
			;;
			-f|--force-yes)
				FORCE_YES='y'
			;;
			--gtest-path)
				bash_gtest_path=$(expandPath "$2")
				shift # past argument
			;;
			--gtest-lib-path)
				bash_gtest_lib_path=$(expandPath "$2")
				shift # past argument
				;;
			--gtest-include-path)
				bash_gtest_include_path=$(expandPath "$2")
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
	echo "Usage: [sudo] bash install.sh [-d|--defaults] [-f|--force-yes] [--gtest-path <arg>] [--gtest-lib-path <arg>] [--gtest-include-path <arg>]"
	echo "	-d --defaults			set script not to prompt about any value which has a default one specified"
	echo "	-f --force-yes			force every prompt to be skiped with 'y' value - use with caution"
	echo "	--gtest-path <arg>		path where GTest project will be downloaded"
	echo "	--gtest-lib-path <arg>		path where GTest shared library will be moved"
	echo "	--gtest-include-path <arg>	path where GTest header files will be moved"
}


# Public function
# Return file extension from given path
# Example:
#	getFileExt '/usr/foo.bar'
#	returns 'bar'
#
function getFileExt() {
	echo ${1##*.}
}

# Public function
# Return file name with its extension from given path
# Example:
#	getFileName '/usr/foo.bar'
#	returns 'foo.bar'
#
function getFileName() {
	echo ${1##*/}
}

# Public function
# Return directory name from given path
# Example:
#	getDir '/usr/foo.bar'
#	returns '/usr'
#
function getDir() {
	echo ${1%/*}
}

# Public function
# Return base directory name from given path
# Example:
#	getDir '/usr/foo/foo.bar'
#	returns '/usr'
#
function getBaseDir() {
	echo ${1%%/*}
}

# Public function
# Expand special character '~'/'.', if occurred, to home/current directory.
# Only first '~'/'.' will be expanded.
# Add '/' as a last character if needed
#
function expandPath() {
	# Expand of ~ character
	local var="${1/#\~/$HOME}"

	# Expand of . character
	local var="${var/#\./$PWD}"

	# Add '/' as a last character if needed
	if ! [[ "$var" =~ '/'$ ]]; then 
		var=$var'/'
	fi

	echo "$var"
}

# Public function
# Read user input and return inputed value or default one (if user left field blank)
#
# Parameters:
#	$1 - text message to show to user before asking for value
#	$2 - default value
# Example:
#	var=$(readData 'Text#1' 'Text#2')
#	returns 'Text#2' or user no-empty input
#
function readData() {
	read -rep "$1 (\"$2\" if left blank): "

	if [ -z "$REPLY" ]; then
		echo "$2"
	else
		echo "$REPLY"
	fi
}

# Private function
# Function supports bash command line arguments.
#
# Parameters:
#	$1 - text message to show to user before asking for value
#	$2 - default value
#	$3 - bash command line argument
# Example:
#	result=$(bash_readData 'Text#1' 'Text#2' "$var")
#	returns
#		- Default value ('Text#2') if $DEFAULT is set to 'y'
#		- Value given by the command line if specified
#		- readData() returned value
#
function bash_readData() {
	if [ "$DEFAULT" == 'y' ]; then
		echo "$2"
	elif ! [ -z "$3" ]; then
		echo "$3"
	else
		echo $(readData "$1" "$2")
	fi
}

# Public function
# Read user input and return inputed value or default one (if user left field blank).
# In both cases special character '~', if occurred, will be expanded to home directory.
# Only first '~' will be expanded.
#
# Parameters:
#	$1 - text message to show to user before asking for value
#	$2 - default value
# Example:
#	var=$(readDir 'Text#1' $(pwd)'/Text#2/')
#	returns absolute path to folder 'Text#2' in current directory or user no-empty input
#
function readDir() {
	local var=$(readData "$1" "$2")

	echo $(expandPath "$var")
}

# Private function
# Function supports bash command line arguments.
#
# Parameters:
#	$1 - text message to show to user before asking for value
#	$2 - default value
#	$3 - bash command line argument
# Example:
#	result=$(bash_readDir 'Text#1' $(pwd)'/Text#2/' "$var")
#	returns bash_readData() expanded value
#
function bash_readDir() {
	local var=$(bash_readData "$1" "$2" "$3")

	echo $(expandPath "$var")
}


# Public function
# Read user input and return inputed value or default one (if user left field blank).
# In both cases special character '~', if occurred, will be expanded to home directory.
# Only first '~' will be expanded.
# If given directory exists then function will ask to delete it first.
#
# Parameters:
#	$1 - text message to show to user before asking for value
#	$2 - default value
# Example:
#	var=$(remakeDir 'Text#1' $(pwd)'/Text#2/')
#	returns absolute path to folder 'Text#2' in current directory or user no-empty input
#
function remakeDir() {
	local var=$(readDir "$1" "$2")
	
	removeIfExists "\"$var\" already exists. Remove this directory?" "$var"
	makeDirIfNotExists "$var"

	echo "$var"
}

# Private function
# Function supports bash command line arguments.
#
# Parameters:
#	$1 - text message to show to user before asking for value
#	$2 - default value
#	$3 - bash command line argument
# Example:
#	var=$(bash_remakeDir 'Text#1' $(pwd)'/Text#2/' "$var")
#	returns bash_readDir() value
#
function bash_remakeDir() {
	local var=$(bash_readDir "$1" "$2" "$3")

	bash_removeIfExists "\"$var\" already exists. Remove this directory?" "$var"
	bash_makeDirIfNotExists "$var"

	echo "$var"
}

# Public function
# Remove file/directory if it exists.
#
# Parameters:
#	$1 - text message to show to user before asking for 'y' or 'n' value
#	$2 - file name/path to directory
#
function removeIfExists() {
	if [ -d "$2" ]; then
		if [ $(confirm "$1") == "y" ]; then
			rm -fr "$2"
		fi;
	fi
}

# Private function
# Function supports bash command line arguments.
#
# Parameters:
#	$1 - text message to show to user before asking for 'y' or 'n' value
#	$2 - file name/path to directory
#
function bash_removeIfExists() {
	if [ -d "$2" ]; then
		if [ $(bash_confirm "$1") == "y" ]; then
			rm -fr "$2"
		fi;
	fi
}

# Public function
# Create given directory if it  exists.
#
# Parameters:
#	$1 - path to directory 
#
function makeDirIfNotExists() {
	if ! [ -d "$1" ]; then
		mkdir -p "$1"
	fi
}

# Private function
# Function supports bash command line arguments.
#
# Parameters:
#	$1 - path to directory 
#
function bash_makeDirIfNotExists() {
	makeDirIfNotExists "$1"
}

# Public function
# Show prompt and force user to confirm or cancel.
#
# Parameters:
#	$1 - text message to show to user before asking for 'y' or 'n' value
#
function confirm() {
	read -e -p "$1 (y/n): "
	echo "$REPLY"
}

# Private function
# Function supports bash command line arguments.
#
# Parameters:
#	$1 - text message to show to user before asking for 'y' or 'n' value
#
function bash_confirm() {
	if [ "$FORCE_YES" == 'y' ]; then
		echo 'y'
	else
		echo $(confirm "$1")
	fi
}

# Public function
# Install additional package and dependencies
#
# Parameters:
#	$1 - package name
#
function installPackage() {
	if [ $(dpkg-query -W -f='${Status}' "$1" 2>/dev/null | grep -c "ok installed") -eq 0 ];
	then
		if [ $(confirm "Confirm installation of package \"$1\"?") == "y" ]; then
			apt-get -yf install "$1"
			apt-get -yf install
		fi;
	else
		echo "Package \"$1\" already has been installed."
	fi;
}

# Public function
# Install additional package and dependencies
#
# Parameters:
#	$1 - package name
#
function bash_installPackage() {
	if [ $(dpkg-query -W -f='${Status}' "$1" 2>/dev/null | grep -c "ok installed") -eq 0 ];
	then
		if [ $(bash_confirm "Confirm installation of package \"$1"\"?) == "y" ]; then
			apt-get -yf install "$1"
			apt-get -yf install
		fi;
	else
		echo "Package '$1' is already installed. Skipping..."
	fi;
}

# Public function
# Updates the cache of the linker with given shared objects
#
# Parameters:
#	$1 - directory of shared libraries to be added
#	$2 - name of a config file to be readed by the linker
#	$3 - directory of configurations for the linker
# Example:
#	addSharedLibToLinker '\usr\local\lib\X' '/etc/ld.so.conf.d/' 'X.conf'
#	will add config file with location of shared libraries in directory '\usr\local\lib\X'
#
function addSharedLibToLinker() {
	echo "Create \"$3\" file in directory \"$2\"..."

	sh -c "echo \"$1\" > \"$2/$3\""

	echo 'Reload system configuration...'
	ldconfig

	echo 'Done.'
}

####################################################################################################################

# Public function
# Checkout given GTest project stable version into given path and move generated static library to given directory.
#
function executeGTestCreation() {
	local gtest_path=$(bash_remakeDir 'Enter where to checkout GTest project' $(pwd)'/GTest/' "$bash_gtest_path")
	local gtest_lib_path=$(bash_remakeDir 'Enter where to move GTest library file' '/usr/local/lib/gtest/' "$bash_gtest_lib_path")
	local gtest_include_path=$(bash_remakeDir 'Enter where to move GTest header files' '/usr/local/include/gtest/' "$bash_gtest_include_path")
	getGTest "$gtest_path" "$gtest_lib_path"
	
	mv "$gtest_path"'googletest/include/gtest/'* "$gtest_include_path"
	echo "GTest header files have been moved to \"$gtest_include_path\"."

	bash_removeIfExists "Delete GTest project sources?" "$gtest_path"
	echo "Done"
}

# Private function
# Checkout GTest project into given path and call makeSharedGTest()
#
# Parameters:
#	$1 - path where GTest project will be checked out.
#	$2 - path where GTest library will be moved.
# Example:
#	getGTest '~/git/GTest' '/home/usr/local/lib/gtest'
#	will download to '~/git/GTest' and generate shared library of project
#	and will move it into '/home/usr/local/lib/gtest' directory.
#
function getGTest() {
	local thisPath=$(pwd)
	echo "\"git\" is needed to checkout GTest project's sources."
	bash_installPackage "git"
	echo "\"pthread\" library will be needed to build GTest form sources."
	bash_installPackage "libpthread-stubs0-dev"

	echo 'Checking out the GTest project...'
	git clone "$gTestGitURL" "$1"

	echo "GTest project has been saved into \"$1\"."
	cd "$1"
	makeSharedGTest "$1" "$2"
	cd "$thisPath"
}

function makeSharedGTest() {
	echo "\"cmake\" is needed to checkout GTest project's sources."
	bash_installPackage "cmake"
	cd "googletest"
	echo "Building 'libgtest.so'..."
	cmake -DBUILD_SHARED_LIBS=ON
	make
	cd ../

	mv "$1"'googletest/libgtest_main.so' "$2"
	mv "$1"'googletest/libgtest.so' "$2"
	echo "GTest static library file has been moved to \"$2\"."

	addSharedLibToLinker "$2" "$sharedLibConfigDir" "$gTestSharedLibConfigFile"
}

function makeStaticGTest() {
	echo "Building 'libgtest.so'..."
	g++ -isystem googletest/include -Igoogletest -pthread -c googletest/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

	mv "$1"'libgtest.a' "$2"
	echo "GTest static library file has been moved to \"$2\"."
}

####################################################################################################################

function executeLog4cxxCreation() {
	bash_installPackage "liblog4cxx10v5"
	bash_installPackage "liblog4cxx10-dev"
	echo "Done"
}

function executeDoxygenCreation() {
	sudo apt-add-repository ppa:dperry/ppa-graphviz-test
	sudo apt-get update
	sudo apt-get autoremove graphviz
	sudo apt-get remove libcdt4
	sudo apt-get remove libpathplan4
	bash_installPackage "graphviz"
}


####################################################################################################################


set -e

pasreBash $@

executeLog4cxxCreation
executeGTestCreation
executeDoxygenCreation
