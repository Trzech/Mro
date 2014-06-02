################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/reader/ColorImageReader.cpp \
../src/reader/GrayscaleImageReader.cpp \
../src/reader/ImageReader.cpp 

OBJS += \
./src/reader/ColorImageReader.o \
./src/reader/GrayscaleImageReader.o \
./src/reader/ImageReader.o 

CPP_DEPS += \
./src/reader/ColorImageReader.d \
./src/reader/GrayscaleImageReader.d \
./src/reader/ImageReader.d 


# Each subdirectory must supply rules for building sources it contributes
src/reader/%.o: ../src/reader/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../src -O0 -g3 -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


