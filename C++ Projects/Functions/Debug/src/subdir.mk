################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Function.cpp \
../src/FunctionOrder.cpp \
../src/Graph.cpp \
../src/main.cpp 

OBJS += \
./src/Function.o \
./src/FunctionOrder.o \
./src/Graph.o \
./src/main.o 

CPP_DEPS += \
./src/Function.d \
./src/FunctionOrder.d \
./src/Graph.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -Ofast -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


