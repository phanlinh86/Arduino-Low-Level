:: Compile, build and upload Arduino
@echo off
:: Arguments
set UPLOAD_OPTION=%1

:: Project related
set PROJECT_NAME=main
set ARDUINO_PORT=COM5


echo PROJECT_NAME: %PROJECT_NAME%
echo ARDUINO_PORT: %ARDUINO_PORT%
echo UPLOAD_OPTION: %UPLOAD_OPTION%
:: Set the Arduino IDE path
set PATH=%PATH%;C:\Users\Phan Linh\Programs\avr8-gnu-toolchain\bin
set PATH=%PATH%;C:\Users\Phan Linh\Programs\avr8-gnu-toolchain\avr\bin
set PATH=%PATH%;C:\Users\Phan Linh\Programs\avrdude-mingw32

:: Check build directory exists
if not exist build ( 
    mkdir build 
) else (
    echo Deleting old build files
    del /Q build\*
)


:: Compile the sketch
echo avr-gcc -Wall -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build\%PROJECT_NAME%.o source\%PROJECT_NAME%%.cpp
avr-gcc -Wall -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build\%PROJECT_NAME%.o source\%PROJECT_NAME%%.cpp

:: Link the sketch
echo avr-gcc -mmcu=atmega328p -o build\%PROJECT_NAME%.elf build\%PROJECT_NAME%.o
avr-gcc -mmcu=atmega328p -o build\%PROJECT_NAME%.elf build\%PROJECT_NAME%.o

:: Convert the elf file to hex
echo avr-objcopy -O ihex build\%PROJECT_NAME%.elf build\%PROJECT_NAME%.hex
avr-objcopy -O ihex build\%PROJECT_NAME%.elf build\%PROJECT_NAME%.hex

:: Upload the hex file to the Arduino
if %UPLOAD_OPTION%==yes (
    echo avrdude -p atmega328p -c arduino -p %ARDUINO_PORT% -b 115200 -U flash:w:build\%PROJECT_NAME%.hex
    avrdude -p atmega328p -c arduino -P "%ARDUINO_PORT%" -b 115200 -U flash:w:build\%PROJECT_NAME%.hex
)
