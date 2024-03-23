BUILDDIR=build

.PHONY: tests
all: libs tests

libs: calc_lib credit_lib deposit_lib


calc_lib:
	cmake . -G "Unix Makefiles" -B $(BUILDDIR) && \
	cmake --build $(BUILDDIR) --target CalculationLib --config=Release


credit_lib:
	cmake . -G "Unix Makefiles" -B $(BUILDDIR) && \
	cmake --build $(BUILDDIR) --target CreditLib --config=Release


deposit_lib:
	cmake . -G "Unix Makefiles" -B $(BUILDDIR) && \
	cmake --build $(BUILDDIR) --target DepositLib --config=Release


tests:
	cmake . -G "Unix Makefiles" -B $(BUILDDIR) && \
	cmake --build $(BUILDDIR) --target CalculationAlgorithmTests --config=RelWithDebInfo
	

style:
	clang-format -i --verbose --style=Webkit *.cpp Model/*.cpp Model/*.h


clean:
	rm -rf $(BUILDDIR)
