BUILDDIR=build

.PHONY: tests
all: tests old bee

old:
	cmake .. -G "Unix Makefiles" -B $(BUILDDIR) && \
	cmake --build $(BUILDDIR) --target CalculationAlgorithmOld

style:
	clang-format -i --verbose --style=Webkit *.cpp Model/*.cpp Model/*.h

lib:
	cmake . -G "Unix Makefiles" -B $(BUILDDIR) && \
	cmake --build $(BUILDDIR) --target CalculationLib --config Release


tests:
	cmake .. -G "Unix Makefiles" -B $(BUILDDIR) && \
	cmake --build $(BUILDDIR) --target CalculationAlgorithmTests --config RelWithDebInfo
	
bee:
	cmake .. -G "Unix Makefiles" -B $(BUILDDIR) && \
	cmake --build $(BUILDDIR) --target CalculationAlgorithm

	g++ -g main.cpp libCalculationAlgorithm.a 

clean:
	rm -rf $(BUILDDIR)
