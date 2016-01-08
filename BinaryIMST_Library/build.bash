#!/bin/bash

#!/bin/bash

appName="BinaryIMST_Library"

# Public function
# Parse command line arguments
#
#	all		build entire project
#	debug		build only 'Debug' configuration
#	shared		build only 'Shared' configuration
#	static		build only 'Static' configuration
#	doc		build documentation only
#
function pasreBash() {
	if [[ $# -eq 0 ]]; then
		buildAll
	fi
	while [[ $# > 0 ]]
	do
		case $1 in
			all)
				buildAll
			;;
			debug)
				buildProject 'Debug' "$appName"
			;;
			shared)
				buildProject 'Shared' "lib$appName.so"
			;;
			static)
				buildProject 'Static' "lib$appName.a"
				;;
			doc)
				buildDoc
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
	echo "Usage: [sudo] bash build.bash [all|debug|shared|static|doc]"
	echo "	all		build entire project"
	echo "	debug		build only 'Debug' configuration"
	echo "	shared		build only 'Shared' configuration"
	echo "	static		build only 'Static' configuration"
	echo "	doc		build documentation only"
}

###########################################################################################

function buildDoc() {
	doxygen "$1"
}

function buildProject() {
	cd "$1"
	make clean
	make -B all
	if [ $? -eq 0 ]; then
		mv "./$2" "../$2"
		echo "Done..."
	fi
	cd ../
}

function buildAll() {
	buildDoc "$appName.Doxyfile"
	buildProject 'Debug' "$appName"
	buildProject 'Shared' "lib$appName.so"
	buildProject 'Static' "lib$appName.a"
}

###########################################################################################

pasreBash $@

