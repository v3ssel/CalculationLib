
all:
	mkdir -p build2 && \
	cd build2 && \
	cmake ../ -G "Unix Makefiles" && \
	cmake --build .

style:
	clang-format -i --verbose --style=Webkit *.cpp Model/*.cpp Model/*.h


tests:
	mkdir -p build && \
	cd build && \
	cmake ../Testing -G "Unix Makefiles" && \
	cmake --build .
	
bee:
	g++ -g main.cpp CalculationAlgorithm\ExpressionParser.cpp \
				 CalculationAlgorithm\Handlers\ExpressionHandler.cpp \
				 CalculationAlgorithm\Handlers\NumberHandler.cpp \
				 CalculationAlgorithm\Handlers\BracketsHandler.cpp \
				 CalculationAlgorithm\Handlers\OperatorsHandler.cpp \
				 CalculationAlgorithm\Handlers\FunctionsHandler.cpp \
				 CalculationAlgorithm\Utils.cpp

clean:
	rm -rf build
