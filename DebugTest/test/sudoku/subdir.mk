################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/sudoku/ClusterReaderUnitTest.cpp \
../test/sudoku/SudokuReaderTest.cpp \
../test/sudoku/SudokuReaderUnitTest.cpp 

OBJS += \
./test/sudoku/ClusterReaderUnitTest.o \
./test/sudoku/SudokuReaderTest.o \
./test/sudoku/SudokuReaderUnitTest.o 

CPP_DEPS += \
./test/sudoku/ClusterReaderUnitTest.d \
./test/sudoku/SudokuReaderTest.d \
./test/sudoku/SudokuReaderUnitTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/sudoku/%.o: ../test/sudoku/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../src -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


