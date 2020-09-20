#!/bin/bash

# Author: Michal Kukowski
# email: michalkukowski10@gmail.com

# Full path of this script
THIS_DIR=`readlink -f "${BASH_SOURCE[0]}" 2>/dev/null||echo $0`

# This directory path
DIR=`dirname "${THIS_DIR}"`

# Chose your install directory, or install to default path
DEFAULT_DIR=~/kmacros
lib_dir=

# Check existing of argument
if [ ! -z "$1" ]; then
    lib_dir=$1
else
    lib_dir=$DEFAULT_DIR
fi

echo "DIR = $lib_dir"

# Create dirs and copy required files
echo "Installing kmacros to $lib_dir ..."
mkdir -p "$lib_dir"
cp -R ./inc/ $lib_dir

echo "DONE"