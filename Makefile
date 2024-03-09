
all:
	mkdir -p build && \
	cd build && \
	cmake ../ -G "Unix Makefiles" && \
	cmake --build .

style:
	clang-format -i --verbose --style=Webkit *.cpp Model/*.cpp Model/*.h
	

clean:
	rm -rf build
