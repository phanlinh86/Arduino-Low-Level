:: Compile, build and upload Arduino
@echo off
:: Arguments
set PROJECT_NAME=%1
set UPLOAD_OPTION=%2

if "%PROJECT_NAME%" == "" (
    echo Usage: build.bat PROJECT_NAME [upload]
    echo PROJECT_NAME: The name of the project
    echo upload: Optional. If set to yes, the hex file will be uploaded to the Arduino
    exit /b
) else if "%PROJECT_NAME%" == "BlinkLed" (
    set PROJECT=1
) else if "%PROJECT_NAME%" == "DisplayClock" (
    set PROJECT=2
) else (
    echo Invalid project name
    exit /b
)

:: Project related
set COMPILE_FILE=main
set ARDUINO_PORT=COM5

echo COMPILE_FILE: %COMPILE_FILE%
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

:: Check date and time
echo %date%
echo %time%
set hour=%time:~0,2%
if "%hour:~0,1%" == " " set hour=0%hour:~1,1%
echo hour=%hour%
set min=%time:~3,2%
if "%min:~0,1%" == " " set min=0%min:~1,1%
echo min=%min%
set secs=%time:~6,2%
if "%secs:~0,1%" == " " set secs=0%secs:~1,1%
echo secs=%secs%

:: Compile the sketch
echo avr-gcc -Wall -Os -DF_CPU=16000000UL -DHOUR=%hour% -DMINUTE=%min% -DSECOND=%secs% -DPROJECT_NAME=%PROJECT_NAME% -mmcu=atmega328p -c -o build\%PROJECT_NAME%.o source\%COMPILE_FILE%%.cpp
avr-gcc -Wall -Os -DF_CPU=16000000UL -DHOUR=%hour% -DMINUTE=%min% -DSECOND=%secs% -DPROJECT=%PROJECT% -mmcu=atmega328p -c -o build\%PROJECT_NAME%.o source\%COMPILE_FILE%%.cpp

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
