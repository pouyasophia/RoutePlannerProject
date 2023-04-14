# Route Planning Project

This repo contains the starter code for the Route Planning project.

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
  
     
 