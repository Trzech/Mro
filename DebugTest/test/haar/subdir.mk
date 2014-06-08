################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/haar/HaarLikeBinarizatorRunner.cpp 

OBJS += \
./test/haar/HaarLikeBinarizatorRunner.o 

CPP_DEPS += \
./test/haar/HaarLikeBinarizatorRunner.d 


# Each subdirectory must supply rules for building sources it contributes
test/haar/%.o: ../test/haar/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../src -O0 -g3 -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


