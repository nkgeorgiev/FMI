################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MyList.cpp \
../src/double_linked_list.cpp \
../src/prog3.cpp 

OBJS += \
./src/MyList.o \
./src/double_linked_list.o \
./src/prog3.o 

CPP_DEPS += \
./src/MyList.d \
./src/double_linked_list.d \
./src/prog3.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


