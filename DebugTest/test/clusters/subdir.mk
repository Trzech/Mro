################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/clusters/ClusterFinderRunner.cpp \
../test/clusters/ClusterFinderTest.cpp \
../test/clusters/ClusterFinderUnitTest.cpp 

OBJS += \
./test/clusters/ClusterFinderRunner.o \
./test/clusters/ClusterFinderTest.o \
./test/clusters/ClusterFinderUnitTest.o 

CPP_DEPS += \
./test/clusters/ClusterFinderRunner.d \
./test/clusters/ClusterFinderTest.d \
./test/clusters/ClusterFinderUnitTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/clusters/%.o: ../test/clusters/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../src -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


