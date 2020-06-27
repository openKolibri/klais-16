# Sixteen Segment Display User Guide
This User guide goes over basic usage instructions. With examples for control with a few systems and languages.

Remmber the transmit of one module or the coroller always goes to the recieve of the next. Its natural to think that the pins should be lined up same to same, but since serial data is unidrectional one device talks (`TX`) and the next one listens (`RX`). Could not count the number of times I've messed this up, you wont break anything, but things just wont work.

All components a RHOS certified and assembly is done in a leadfree process.

## Contents
In the package you will recieve a labelled, programed, and tested display module in its default conifguration. Assembled with 3 mm x 7.5 mm plastic push rivets. 

## Required Tools

### Soldering Iron
You will need to some really minimal soldering that is very forgiving. I am currenty using my portable TS100 soldering iron set at 350C. Along with the soldering iron you will need solder, I prefer rosin core leaded solder (Kester 60/40) which is easier to work with, but lead free should be completely serviceable (you might need to bump up the temperature to 400C for lead free).

### Mounting Method
If you are mounting on aluminum extrusion, you will need allen keys or screwdrivers for the screws you are using (I use 2.5mm Boondus balldriver for M3 socket cap screws). Alternetively if mounting to wood with #4 screws you will need a drill/driver and as well as possibly a spade bit to make clearence for the joints. 

![toolsAndParts]

## Assemlbing a Array

[screwing togeether gif]

After mounting the segments, the contacts are bridged for the data flow.
Soldering iron at 350 C (675 F) and heat up both pads and flow solder until a bridge is formed. 

[soldering gif]

## Disassembly
Reheat the solder joint with a clean tip to pick up some solder and unridge the connection. If needed the pads can then be cleaned with an iron at 400 C (750 F) and solder wick.

[desolder gif]

Then unmount the modules.

[Disassebmly gif]

## Surface Repair
The surface coating of soldermask is fairly robust (TAIYO INK PSR-2000) but if scratches appear, black matte nail polish can be used to apply another coat as a close match.

[blackPolishGif]

## Writing
The data in the segments is shifted across when a new character is sent. In order to show characters in a left to right format, they will need to be sent in reverse. 

This can be done with built in tools like `rev` in linux, maunally by encoding the string backwards, or through looping the string in reverse and sending one character at a time. 

No custom libraries are needed for most platforms, as basic UART functionality already exits in hardware. This allows communication from a verity of machines from early home computers, microcontrollers, and laptops.

### Basic examples
Basic examples are provided for a number of diffrent languages and microcontroller environments for outputing a string to the display.

#### Windows Batch File
Run the following commands (directly or in a `.bat` file) to set up COM** and output the string.
```cmd
mode COM** BAUD=115200 PARITY=n DATA=8
set /p x="olleh" <nul >\\.\COM**
```

#### ✓ Bash
Run the following commands (directly or in a `.sh` file). Outputs on /dev/sttyS***
```bash
stty -F /dev/ttyS*** 115200 cs8 -cstopb -parenb 
echo -ne "Hello" | rev > /dev/sttyS***
```

#### Node.js
Install the `serialport` dependency.
```bash
npm install --save serialport
```
Then directly in the interperter or in the `main.js` file.
```node
const SerialPort = require("serialport");
const port = new SerialPort(/dev/ttyS0, { baudRate: 115200 });
port.write("Hello".split("").reverse().join(""));
```

If in the `main.js` file, run it from the command line.
```bash
node ./main.js
```

#### ✓ Arduino
Minimal program for arduino.
```arduino
void setup(){
    Seiral.begin(115200);
    Serial.print("olleH");
}
void loop(){

}
```

#### Micrpython/Circuitpython
In minimal program in `main.txt`.
```pyhton
import board
import busio
 
uart = busio.UART(board.TX, board.RX, baudrate=115200)
print("Hello"[::-1])
```


#### AVR (Attiny10)
```c

```

#### AVR ASM
```asm
```

#### Fortran
```fortran
    USE IFPORT
    SPORT_WRITE_DATA( 2, 'olleH', 5 )
    END
```

#### STM8S SPL
```c

```



<!-- Images -->
[toolsAndParts]:             ./docs/userGuide/toolsAndParts.jpg