################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/binarization/Binarizator.cpp \
../src/binarization/BrodleyBinarizator.cpp \
../src/binarization/IntegralImageBuilder.cpp \
../src/binarization/SauvolaBinarizator.cpp 

OBJS += \
./src/binarization/Binarizator.o \
./src/binarization/BrodleyBinarizator.o \
./src/binarization/IntegralImageBuilder.o \
./src/binarization/SauvolaBinarizator.o 

CPP_DEPS += \
./src/binarization/Binarizator.d \
./src/binarization/BrodleyBinarizator.d \
./src/binarization/IntegralImageBuilder.d \
./src/binarization/SauvolaBinarizator.d 


# Each subdirectory must supply rules for building sources it contributes
src/binarization/%.o: ../src/binarization/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../src -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


