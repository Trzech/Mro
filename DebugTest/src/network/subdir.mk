################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/network/NeuralNetwork.cpp \
../src/network/T_Backprop.cpp 

OBJS += \
./src/network/NeuralNetwork.o \
./src/network/T_Backprop.o 

CPP_DEPS += \
./src/network/NeuralNetwork.d \
./src/network/T_Backprop.d 


# Each subdirectory must supply rules for building sources it contributes
src/network/%.o: ../src/network/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../src -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


