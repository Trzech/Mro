################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/binarization/BrodleyBinarizatorRunner.cpp \
../test/binarization/IntegralImageBuilderUnitTest.cpp \
../test/binarization/SauvolaBinarizatorRunner.cpp 

OBJS += \
./test/binarization/BrodleyBinarizatorRunner.o \
./test/binarization/IntegralImageBuilderUnitTest.o \
./test/binarization/SauvolaBinarizatorRunner.o 

CPP_DEPS += \
./test/binarization/BrodleyBinarizatorRunner.d \
./test/binarization/IntegralImageBuilderUnitTest.d \
./test/binarization/SauvolaBinarizatorRunner.d 


# Each subdirectory must supply rules for building sources it contributes
test/binarization/%.o: ../test/binarization/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../src -O0 -g3 -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


