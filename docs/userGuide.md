# Sixteen Segment Display User Guide
This guide goes over basic usage instructions on how to implement the display into what you are making, a far more detailed [technical manual][readme] is also available. With examples for control with a few systems and languages.

Make sure you discharge any static electricity on a ground point before working on assembling any displays.

## Contents
In the package you will recieve a labelled, programed, and tested display module in its default conifguration. Assembled with `3 mm` x `7.5 mm` plastic push rivets. 

## Required Tools

### Soldering Iron
You will need to do some really minimal soldering that is very forgiving. I am currenty using my portable TS100 soldering iron set at 350C. 

Along with the soldering iron you will need solder, I prefer rosin core leaded solder (Kester 60/40) which is easier to work with, but lead-free should be completely serviceable (you might need to bump up the temperature to 400C for lead-free). Separate flux is also helpful to have, but probably not needed.

All components and the assembly are RHOS certified and a full lead-free process is used. If you are using leaded solder, you might need to dilute the lead-free solder with leaded for better wetting when soldering.


![toolsAndParts]

## Mounting Method
There are quite a few mounting methods but I will go over a few of my favorites, depending on the look you want.

If you are mounting on aluminum extrusion, you will need allen keys or screwdrivers for the screws you are using (I use 2.5 mm Boondus balldriver for M3 socket cap screws). Alternatively if mounting to wood with #4 screws you will need a drill/driver and possibly a spade bit to make clearence for the joints. 

### Canvas frame
Using canvas strechers to make a square frame, or even just wooden 1x2 that have been planed with #4 or 3 mm pan head wood screws is a quick assembly process. Drill pilot holes for mounting before driving in the screws, as the chance of splitting is high with thin pieces. If you use a whole backing board, you will need to drill clearance holes for the connections in the back.

### 15 mm Aluminum Extrusion
Aluminum extrusion like Misumi 1515 or OpenBeam is easy to cut to length with a hacksaw, and can mount with M3 screws. No holes need to be drilled and at least two screws per module ensures everything is kept in square.

[screwing togeether gif]

### 20 mm Aluminum Extrusion
The panels, if joined together with pins for lignment, can be slid into the slots in Misumi 2020 or 80/20 metric extrusion. They can be secured in place with slot covers or T-nuts with grub screws.

[Sliding into extrusion gif]

## Assemlbing a Array
After mounting the segments, the contacts are bridged for the data flow. Just add solder until it builds up to the point that it bridges over. You can also use a small piece of wire in place to make the solder bridge easier. The contacts are placed 0.1 in apart so header pins could also be used if bent into place.

[soldering gif]

Then on the first panel connect in the data from the controller or computer as well as `+5V` and `GND` pins. Be wary of current requrements, exact numbers for each character and brightness vaules are available in a [table], but each module can draw a max current of about 320 mA so make sure your power supply is sufficently rated.

[connecting to first panel]

Remember the transmit of one module or the controller always goes to the recieve of the next. Its natural to think that the pins should be lined up same to same, but since serial data is unidrectional one device talks (`TX`) and the next one listens (`RX`). I can not count the number of times I've messed this up. You won't break anything, but things just won't work if you install a panel upside down.

If you want to use a baud rate other than 115200 bits per second, you can bridge the config pads to select one of the 15 alternative bitrates from the [configuration table].

## Disassembly
Reheat the solder joints with a clean tip to pick up some solder and unbridge the connection. If needed the pads can then be cleaned with an iron at 400 C (750 F) and solder wick. 

[desolder gif]

## Surface Repair
The surface coating of soldermask is fairly robust (TAIYO INK PSR-2000) but if scratches appear, black matte nail polish can be used to apply another coat as a close match.

[blackPolishGif]

## Writing
The data in the segments is shifted across when a new character is sent. In order to show characters in a left to right format, they will need to be sent in reverse. 

This can be done with built in tools like `rev` in linux manually, by encoding the string backwards, or through looping the string in reverse and sending one character at a time. 

No custom libraries are needed for most platforms, as basic UART functionality already exits in hardware. This allows communication from a variety of machines from early home computers, microcontrollers, and laptops.

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

<!-- Internal Links -->
[readme]:                    ../readme.md


<!-- Images -->
[toolsAndParts]:             ./userGuide/toolsAndParts.jpg
