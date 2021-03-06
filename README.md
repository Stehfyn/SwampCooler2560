<div align="center">

# SwampCooler2560

A state-managed swamp cooler targeting the [Arduino Mega 2560](https://docs.arduino.cc/hardware/mega-2560)

<img src="https://raw.githubusercontent.com/Stehfyn/SwampCooler2560/c500ab42bb0f8f0503ba2b2f96ac1333bf7baf19/assets/demo.png">


</div>

## Install
First, grab the repo:
```bash
git clone https://github.com/Stehfyn/SwampCooler2560
```
Then execute:
```bash
./SwampCooler2560/scripts/install.sh [path-to-your-arduino-libraries-folder]
```
## External Dependencies
<p>
<a href="https://github.com/arduino-libraries/LiquidCrystal" style="text-decoration-line: none;">LiquidCrystal</a>

<a href="https://github.com/winlinvip/SimpleDHT" style="text-decoration-line: none;">SimpleDHT</a>

<a href="https://github.com/NorthernWidget/DS3231" style="text-decoration-line: none;">DS3231</a>

<a href="https://github.com/PalladinoMarco/AlignedJoystick" style="text-decoration-line: none;">AlignedJoystick</a>
</p>

## Usage

After installing SwampCooler2560 and its external dependencies, simply include the main header:

```cpp
#include <SwampCooler2560>
```
To instantiate with the default pin map:
```cpp
SwampCooler2560 sc;
```
or a custom one:
```cpp
SwampCooler2560 sc (SwampCooler2560PinMap(
        7,   //power switch

        A0,  //joystick right delta
        A1,  //joystick left delta

        3,   //disabled led
        4,   //idle led
        5,   //running led
        6,   //error led

        35,  //lcd register select
        33,  //lcd enable
    
        //The next four parameters are for the lcd's data bits in 4-bit mode
        //ordered from least significant to most significant
    
        31,       //lcd data bit (least significant bit)
        29,       //lcd data bit
        27,       //lcd data bit 
        25,       //lcd data bit (most significant bit)

        22,       //DHT11 data
        A2,       //water sensor data

        SDA,      //I2C serial data (SDA)
        SCL,      //I2C serial clock (SCL)

        2,        //fan motor (DC driven)
        13 ));     //servo motor (AC driven)
```
and finally:
```cpp
void setup(){
    sc.begin();
}

void loop(){
    sc.update();
}
