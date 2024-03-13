.PHONY: tests
all: tests old bee

old:
	mkdir -p build && cd build && \
	cmake .. -G "Unix Makefiles" && \
	cmake --build . --target CalculationAlgorithmOld

style:
	clang-format -i --verbose --style=Webkit *.cpp Model/*.cpp Model/*.h


tests:
	mkdir -p build && cd build && \
	cmake .. -G "Unix Makefiles" && \
	cmake --build . --target CalculationAlgorithmTests
	
bee:
	mkdir -p build && cd build && \
	cmake .. -G "Unix Makefiles" && \
	cmake --build . --target CalculationAlgorithm

	g++ -g main.cpp libCalculationAlgorithm.a 

clean:
	rm -rf build
