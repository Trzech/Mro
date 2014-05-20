################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/sudoku/SudokuReader.cpp 

OBJS += \
./src/sudoku/SudokuReader.o 

CPP_DEPS += \
./src/sudoku/SudokuReader.d 


# Each subdirectory must supply rules for building sources it contributes
src/sudoku/%.o: ../src/sudoku/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../src -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


