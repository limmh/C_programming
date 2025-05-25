#!/bin/bash

if [ ! -d "builds" ]; then
	mkdir builds
fi

cmake -S . -B builds
cd builds
make all
cd ..
