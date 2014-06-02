################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/clusters/ClusterFindeTest.cpp \
../test/clusters/ClusterFinderRunner.cpp 

OBJS += \
./test/clusters/ClusterFindeTest.o \
./test/clusters/ClusterFinderRunner.o 

CPP_DEPS += \
./test/clusters/ClusterFindeTest.d \
./test/clusters/ClusterFinderRunner.d 


# Each subdirectory must supply rules for building sources it contributes
test/clusters/%.o: ../test/clusters/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../src -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


