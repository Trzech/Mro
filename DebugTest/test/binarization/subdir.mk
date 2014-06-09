################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/binarization/BrodleyNonUnitTests.cpp \
../test/binarization/IntegralImageBuilderTest.cpp \
../test/binarization/SauvolaNonUnitTests.cpp 

OBJS += \
./test/binarization/BrodleyNonUnitTests.o \
./test/binarization/IntegralImageBuilderTest.o \
./test/binarization/SauvolaNonUnitTests.o 

CPP_DEPS += \
./test/binarization/BrodleyNonUnitTests.d \
./test/binarization/IntegralImageBuilderTest.d \
./test/binarization/SauvolaNonUnitTests.d 


# Each subdirectory must supply rules for building sources it contributes
test/binarization/%.o: ../test/binarization/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../src -O0 -g3 -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


