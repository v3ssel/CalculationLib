
all:
	mkdir -p build && \
	cd build && \
	cmake ../ -G "Unix Makefiles" && \
	cmake --build .

style:
	clang-format -i --verbose --style=Webkit *.cpp Model/*.cpp Model/*.h


# tests:
# 	g++ -g main.cpp NewModel/BaseCalculation.cpp NewModel/CalculationModel.cpp NewModel/Utils.cpp

tests:
	mkdir -p build && \
	cd build && \
	cmake ../Testing -G "Unix Makefiles" && \
	cmake --build .
	

clean:
	rm -rf build
