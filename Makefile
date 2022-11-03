

.PHONY: build build_win


# setup development environment
setup:
	@echo 'setup development environment...'
	@chmod +x ./scripts/setup.py && ./scripts/setup.py -f ./scripts/libraries.json -d -b

# build linux
build:
	@echo 'build linux platform...'
	@rm -rf build
	@mkdir build && cd build && cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain-gcc.cmake .. && make
	@cd ..

# build windows
build_win:
	@echo 'build windows platform...'
	@rm -rf build_win
	@mkdir build_win && cd build_win && cmake -DCMAKE_TOOLCHAIN_FILE=./toolchain-mingw.cmake .. && make
	@cd ..


test:
	@echo 'run unit test...'
	@rm -rf build_test
	@mkdir build_test && cd build_test && cmake ../tests/ && make


clean:
	@rm -rf build
	@rm -rf build_win
	@rm -rf build_test
	@rm -rf bin

