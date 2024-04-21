# Route Planning Project

This repo contains the code for a Route Planning project. All source code located in src/ directory. Program requires a starting and ending x, y coordinate pair. Starting coordinates must be greater than or equal to 0 and less than or equal to 100. Upon compiling and executing OSM_A_star_search, the user will enter starting and ending coordinates. The program will display a graphic rendering of the fatest route between the coordinates and write the total distance to the terminal.  

## Compiling and Running

### Compiling

mkdir build && cd build

cmake ..
make

### Running

from `build`:

./OSM_A_star_search

## Testing

from `build`:

./test

## Troubleshooting Tips for IO2D Installation  

	sudo apt update
	sudo apt install build-essential
	sudo apt install cmake
	sudo apt install libcairo2-dev
	sudo apt install libgraphicsmagick1-dev
	sudo apt install libpng-dev

	git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
	cd P0267_RefImpl
	mkdir Debug
	cd Debug
	cmake --config Debug "-DCMAKE_BUILD_TYPE=Debug" ..
	cmake --build .
	sudo make install
  
     
 