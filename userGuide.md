# Sixteen Segment Display User Guide
This User guide goes over basic useage instrucitons. With examples for a veirty of systems.


All components a RHOS certified and assembly is done in a leadfree process.

## Contents
One labelled, flashed, and tested display module in its default conifguration. Assembled with 3 mm x 6.5 mm plastic push rivets (or M3x8 SS machine screws and nuts for first batch). 

## Required Tools
Soldering Iron (Using my portable TS100 Iron)
Flux core solder (Kester leaded solder is my favorite)

If mounting on 15mm extrusion
M2.5 Allen key (I like Boondus balldrivers)

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

#### Bash
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
The ndirectly in the interperter or in the `main.js` file.
```node
const SerialPort = require("serialport");
const port = new SerialPort(/dev/ttyS0, { baudRate: 115200 });
port.write("Hello".split("").reverse().join(""));
```

If in the `main.js` file, run it from the command line.
```bash
node ./main.js
```

#### Arduino
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
```

#### STM8S SPL
```c

```