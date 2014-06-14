################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/haar/HaarLikeBinarizator.cpp 

OBJS += \
./src/haar/HaarLikeBinarizator.o 

CPP_DEPS += \
./src/haar/HaarLikeBinarizator.d 


# Each subdirectory must supply rules for building sources it contributes
src/haar/%.o: ../src/haar/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../src -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


