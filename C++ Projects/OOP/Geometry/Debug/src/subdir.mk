################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Geometry.cpp \
../src/Line.cpp \
../src/Matrix.cpp \
../src/Plane.cpp \
../src/Point.cpp \
../src/Vector.cpp 

OBJS += \
./src/Geometry.o \
./src/Line.o \
./src/Matrix.o \
./src/Plane.o \
./src/Point.o \
./src/Vector.o 

CPP_DEPS += \
./src/Geometry.d \
./src/Line.d \
./src/Matrix.d \
./src/Plane.d \
./src/Point.d \
./src/Vector.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


