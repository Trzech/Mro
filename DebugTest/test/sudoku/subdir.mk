################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/sudoku/Copy\ of\ SudokuReaderUnitTest.cpp \
../test/sudoku/SudokuReaderTest.cpp 

OBJS += \
./test/sudoku/Copy\ of\ SudokuReaderUnitTest.o \
./test/sudoku/SudokuReaderTest.o 

CPP_DEPS += \
./test/sudoku/Copy\ of\ SudokuReaderUnitTest.d \
./test/sudoku/SudokuReaderTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/sudoku/Copy\ of\ SudokuReaderUnitTest.o: ../test/sudoku/Copy\ of\ SudokuReaderUnitTest.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../src -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -MMD -MP -MF"test/sudoku/Copy of SudokuReaderUnitTest.d" -MT"test/sudoku/Copy\ of\ SudokuReaderUnitTest.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

test/sudoku/%.o: ../test/sudoku/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../src -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


