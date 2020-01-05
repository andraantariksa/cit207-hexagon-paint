build: create-cmake
	cd build/ && make

create-build-dir:
	mkdir -p build/

create-cmake: create-build-dir
	cd build/ && cmake ..