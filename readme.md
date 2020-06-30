![SIXTEEN]
![SEGMENT]
![DISPLAY]

# Sixteen Segment Display
The look of classic signage, be it neon tubes, wrought iron, or the use of distinctive typography and negative space, has a particular appeal. Unfortunately, the art form is dwindling due to the flexibility and flash that comes with newer LED arrays. Their distinctive styles have been giving way for the monotony of RGB LED panels.

![cycleGif]

The *Klais Display* series, in which this panel is the first item, was inspired by the early electronic displays still seen in relics bygone from an era of cigarette machines, electronics test equipment, and pinball machines. Its been modernized, enlarged, and made easily integrable into your own projects, while retaining its beauty and elegance.

![isoArray]

What follows below is highly detailed technical documentation. The [user guide][userGuide] is also available and focuses on integrating the display(s) into a project.

## Table of Contents
  * [Design](#design)
    * [Hardware](#hardware)
      * [LEDs](#leds)
      * [LED Driver](#led-driver)
      * [Microcontroller](#microcontroller)
      * [Power supply](#power-supply)
      * [Connections](#connections)
        * [Programming](#programming)
        * [Dataflow](#dataflow)
        * [Config Pads](#config-pads)
        * [Key Connector](#key-connector)
      * [Mounting](#mounting)
    * [Firmware](#firmware)
      * [Modes](#modes)
      * [UART](#uart)
        * [RX](#rx)
        * [TX](#tx)
      * [Brightness](#brightness)
      * [Timeout Refresh](#timeout-refresh)
      * [Display Driver](#display-driver)
        * [Protocol](#protocol)
        * [LED Number](#led-number)
        * [Segment Order](#segment-order)
      * [Configuration](#configuration)
        * [Baud Selection](#baud-selection)
      * [Compiling](#compiling)
      * [Flashing](#flashing)
  * [Absolute Maximum Ratings](#absolute-maximum-ratings)
  * [Guaranteed Ratings](#guaranteed-ratings)
  * [Manufacturing](#manufacturing)
    * [BOM](#bom)
    * [PCB-Assembly](#pcb-assembly)
    * [Physical Assembly](#physical-assembly)
    * [Production Scaling](#production-scaling)
      * [PCB Stack](#pcb-stack)
      * [Die Cut](#die-cut)
      * [Injection Moulding](#injection-moulding)
      * [Custom ASIC](#custom-asic)
    * [Programmer](#programmer)
      * [Minimal](#minimal)
      * [Production](#production)
    * [Artwork](#artwork)
    * [Labels](#labels)
    * [Inventory and QC](#inventory-and-qc)
    * [Part Numbers](#part-numbers)
  * [Safety](#safety)
  * [Certifications](#certifications)
  * [Licence](#licence)
  * [Attribution](#attribution)
    * [Fonts](#fonts)
    * [Libraries](#libraries)
  * [Reccomended Reading](#reccomended-reading)
  * [ToDo](#todo)


## Design
The display is a recreation of sixteen segment alphanumeric displays in a format that is physically larger and thinner than anything available on the viewing front. The modular segments can be combined to make a display of any length. It is designed to be easy to use and accessible. The physical design is based on stacking layers to provide clearance, a diffusion layer, and encapsulation for the electronics. The minimalist design and 3:2 aspect ratio were chosen to make integration very clean. There are no gaps between characters and when placed side-by-side, there is a flat near-seamless surface.

| NOON               | MDNT               | BASE               |
| ------------------ | ------------------ | ------------------ |
| ![SEG-16-RED-NOON] | ![SEG-16-RED-MDNT] | ![SEG-16-RED-BASE] |

### Hardware
The panels are designed for efficient high yield manufacturing in both small and large quantities, with three possible stages, based on tooling investment. The physical size of each panel is `100 mm` x `66.66 mm`, providing a 3:2 aspect ratio and are nominally `5.8 mm` thick. Each panel weighs `63.97 g` with 6 plastic rivets.

![schematic]

A [schematic.pdf] is also available.

#### LEDs
The assembly uses 128 0603 surface mount LEDs. They are spaced evenly through all the segments, as well as eight of them acting as points in the underline. The 0603 (`60 mil` x `30 mil`, or `1.5 mm` x `0.8 mm`) package is used for their wide accessibility, providing a breadth of alternatives in color, lens projection angle, and brightness for possible substitutions. The datasheets for the LEDs used for each model is provided in the table below.

| Model             | MPN        | Detail          | Current Draw         |
| ----------------- | ---------- | --------------- | -------------------- |
| `SEG-16-RED-XXXX` | [KT-0603R] | ![IMG-KT-0603R] | [RED][asciiCurrent]  |

#### Led Driver
Titan Micro Electronic's [TM1640] ([english][TM1640ENG]) is used to control the LEDs. The device provides individual control of 128 LEDs in a 16x8 multiplexing configuration, has 8 levels of brightness adjustment, and provides a constant current supply of `20 mA`. It is rated for only `5V` but testing shows that, although with a slightly lower multiplexing frequency, it works quite well at `3.3V`. Communication is over a clocked serial link with a custom protocol and register mappings control the outputs. The 16 grids are rows, while the eight segments are the columns.

![IMG-TM1640]

This chip is made specifically for the Chinese market and may be hard to source in the west. Based on datasheets, it is easily swappable with identical components from other manufacturers, as shown below, in case the availability changes.

| Manufacturer            | MPN      |
| ----------------------- | -------- |
| GN Semiconductors       | GN1640   |
| Cmsemicon               | CMS1640  |
| Wuxi I-CORE Electronics | AiP1640  |

#### Microcontroller
STMicroelectronics's [STM8S003] is a very low-cost microcontroller for cost sensitive applications, but provides a reasonable host of features. It has a wide voltage range of `2.95V` to `5.5V`, internal 16Mhz clock, UART that can be clocked at up to 1Mbps, plenty of timers, and 28 I/O. As well as other features that are not being used like a 10b ADC, SPI/I2C hardware, and low power modes.

![IMG-STM8S003]

#### Power supply
The input power is rated at `5V`, and the current drawn is dependent on the number of lit LEDs and the color of the display. Each segment has `100 uF` + `10 uF` of bulk capacitance, as well as decoupling on all the chips so it should be robust against a unstable power supply. There is no reverse polarity or overvoltage protection as that is the responsibility of the integrator. The table below shows some current draws, with the full table of all the models and characters [available][asciiCurrent] along with measurement methodology.

| Display  | `RED` Full Brightness (mA) | `RED` Min Brightness (mA) |
| -------- | --------------------------:| -------------------------:|
| Off      |                        5.2 |                       5.2 |
| All      |                      319.0 |                      28.6 |
| `@`      |                      197.0 |                      19.1 |
| `.`      |                       17.1 |                       6.0 |
| `K`      |                      125.7 |                      13.8 |
| `[`      |                      106.0 |                      12.4 |

Maximum power draw is `1.6 W` at max brightness and all segments lit. Temperature rise above ambient after two hours is `15.9°C` (`61°F`).

#### Connections
The back of the module contains pads that are used for communication and configuration, providing many options to the end-user.

![config-back]

##### Programming
The four labeled pads near the top of the module are for programming. The STM8S uses a `SWIM` programming interface. The `4 mm` round pads are used to install the initial firmware and can be used for firmware updates or custom firmware if needed. The power pins are connected to the power rails, so they can also be used as power input or outputs.

![config-pgrm]

##### Dataflow
The five pads on each side are the connections that provide the data, as well as power rails, from one board to another. For basic functionality, lining up the boards and soldering the top three pads (`GND`, `TX/RX`, and `+5V`) is all that is needed, although soldering all five will provide more power rails and cause no issues.

![config-dataflow]

With the display facing you, the data comes in on the left on the `RX` pad, and flows out on the right via the `TX` pad. If the modules are soldered inverted, the connection is symmetric providing protection against swapping power supply rails.

If needed, the inverted configuration also provides the option of having two decimal points forming a colon. For this configuration to work, the solder jumper pads on the back will need to be reconfigured, cutting the top two and bridging the bottom, as shown in the diagram.

![config-dataflowInv]

The moves the `RX` and `TX` lines to the correct sides to be placed inline with normally oriented modules.

##### Config Pads
The back has seven configuration pads that provide different settings and are checked on boot. By default, they are all unbridged. The configuration pads are to be selected with solder jumpers.

![config-config]

##### Key Connector
The front contains two optional unpopulated spring connectors Molex [0472861001]. These provide functionality if the thickness of the panel or reconfigurability is the main concern. By removing any solder joints on the back, and transmitting the data and power through the keyed connector. The thickness is limited to `5.8 mm`. The small PCB keys also allow assembly and construction of quick and easily reconfigurable arrays. The connectors are not always used, so they are not installed by default since they add cost and are not expected to be used by most.

![config-keyed]

The solder jumper marked `RTN_EN` enables the return channel on the last board. If a chain of displays is used and needs to be chained to the next row, this will send the signal back though one of the spring connector pins and make it available on the first display making a for a cleaner run of signal between rows.

#### Mounting
The mounting holes are placed `3 mm` from all edges and are for `M3` screws in a very close fit with a `3.1 mm` drill and though plated for a bit more ruggedness. A `#4` screw can be used as a imperial alternative. They are not connected to any nets, have a `5.5 mm` annular ring for screw heads, and are masked so if screws are not used, the annular ring surface matches the rest of the panel.

![mountingDim]

The holes and hardware provide a number of options for assembly and mounting.

| Mounting Method              | Part Number                                      | Component         | Example               |
| ---------------------------- | ------------------------------------------------ | ----------------- | --------------------- |
| Push Rivet `3 mm` x `7.5 mm` | [R3075]                                          | ![plasticRivet]   | ![rivetInstalled]     |
| Spring pin `3 mm` x `6 mm`   | [97161A128]                                      | ![springPin]      | ![springPinInstalled] |
| `M3x8x0.5` and Nut           | [91292A112] [91828A211]                          | ![M3x8]           | ![M3x8Installed]      |
| `15 mm` Extrusion M3x10      | [Misumi HFS3], [OpenBeam], [Makerbeam XL]        | ![openbeamParts]  | ![openbeamInstalled]  |
| `10 mm` Extruison M3x8       | [MakerBeam], [MicroRAX]                          | ![makerbeamParts] | ![makerbeamInstalled] |
| `20 mm` Extrusion Slot       | [Misumi HFS5], [Metric 8020]                     | ![2020Extrusion]  | ![2020Installed]      |
| Soldered brass nut           | [90690A037]                                      |                   |                       |
| Zip Ties `3 mm`              |                                                  |                   |                       |
| #4 screw, machine or wood    |                                                  |                   |                       |
| Pop rivets, M3 or #4         |                                                  |                   |                       |

### Firmware
The firmware is written in C and is fully interrupt driven. It uses the [STM8 standard periphiral library][STM8SPL] (SPL) and provides multiple modes of controlling the display through commands. All code shown is simplified pseudocode.

#### Modes
By default the display boots in the `ASCII` character mode operating as a state-machine making changes based on each byte received. When enough bytes have been received for the command, the device shifts back into `ASCII` mode.

| Mode       | Control Byte | Bytes | Notes                       |
| ---------- | ------------ | -----:| --------------------------- |
| ASCII      | None         |     0 | Displays ASCII cahrachter   |
| Segment    | 0x11 `DC1`   |     2 | Control individual segments |
| LED        | 0x12 `DC2`   |    16 | Control individual LEDs     |
| Brightness | 0x13 `DC3`   |     1 | Set brightness              |

**Only ASCII mode is verified in firmware version 0.6 other modes are in beta**

#### UART
The UART hardware is used to receive and transmit data from a module to another. Communication is through an 8 bit NRZ with one start bit and one stop bit encoding with no parity and the default baud rate is `115200 bps`. The voltage levels are the module power voltage, nominally `5V`.

The UART is initialized on boot and the receive interrupt is enabled. When a new character has been read in the receive buffer, the interrupt fires.

##### RX
Based on the receive mode the new data is loaded into the receive buffer. A number of consecutive bytes read is dependent on the mode that is set. A mode byte received after mode has been reset will change the mode as well. The transmit interrupt is fired when a new byte is received and the buffer is full, depending on the current receive mode.

##### TX
The first byte is sent by the interrupt trigger. Depending on the transmit mode, the interrupts continue to fire, stepping down through the buffer until it is empty, outputting the data in the same order as it was received.

#### Brightness
There are nine brightness levels including blanking. They are accessed with sending the brightness mode selector followed by the brightness code.

| Level | Code (HEX) | Code (DEC) |
| -----:| ---------- | ----------:|
|   OFF | 0x81       |        129 |
|     1 | 0x88       |        136 |
|     2 | 0x89       |        137 |
|     4 | 0x8A       |        138 |
|    10 | 0x8B       |        139 |
|    11 | 0x8C       |        140 |
|    12 | 0x8D       |        141 |
|    13 | 0x8E       |        142 |
|    14 | 0x8F       |        143 |

#### Timeout Refresh
A display refresh timeout is implemented so the display only updates when there is a pause in the data. This prevents the display from flickering with intermediate data when a stream of data is being loaded into an array. This also updates all displays at the exact same time, since the time from the last byte is the same across all displays in an array.

```c
UART_RX_INTERRUPT() {
  TIMER_SET(0x00);
  TIMER(INTERRUPT, ENABLE);

  // Remaining RX routine ...
}
```

Every time a new character is received in the RX buffer, a timeout is started of 1 ms (*to be replaced with 2.5 byte time based on baud rate*). If a new character comes before the timeout is reached, it is reset again. When the timeout is reached, the overflow interrupt is triggered. In the interrupt, the further interrupts are disabled and then the display is drawn based on the TX mode.

```c
TIMER_INTERRUPT(){
  TIMER(INTERUPT, DISABLE);
    switch (txMode) {
        case LED_CONTROL:
          showLeds(data);
          break;
        case SEGEMENT_CONTROL:
          showSegments(data);
          break;
        case BRIGHTNESS_CONTROL:
          setBrightness(data);
          break;
        default:
          showLetter(data);
    }
}
```

#### Display Driver
The display driver is a minimal custom library. The display driver is controlled over a clocked serial link with a custom protocol. The LEDs are multiplexed based on the internal memory that stores a 1b value for each LED.

The chip has only a few registers, most of which make up the current LED states. They are all described in the header file and fall into three sections.

- Data Commands
- Grid Memory
- Display Brightness

##### Protocol
A few requirements define the protocol.

- Default state for both clock and data is high
- Start condition is data going low followed by clock going low
- A bit is read when the clock is pulsed positive
- Data cannot change while clock is high
- End condition is clock high followed by data high
- 8 bits per byte, LSB First

![TM1640Timing]

Registers are set by sending a command byte followed by a optional data byte based on the command. A set of commands can be sent if auto increment mode is set by not fulfilling the end condition and sending the next byte immediately.

![dataCapImg]

A Saleae logic [capture][dateCapFile] is also provided.

##### LED Number
The LEDs are placed in a grid-like pattern, so a conversion is needed to map each LED to the segment it's in. [segmentMapping.h] contains arrays that map the LED's reference designator to each segment. This still needs to be converted into the segments and grid from the LED number. The formula below is used to make those conversions.

```
GRID = ((REF-1) / 8) + 1
SEG = (REF-1) % 8
```

##### Segment Order
Besides direct control over the LEDs, there are also helper functions such as segment control and print letter. These use the [segmentMapping.h] and [sixteenSegments.h] headers. Once the LEDs are mapped to the segments, the segments are mapped to the ASCII character set. [sixteenSegments.h] contains which segments need to be lit for each character, the notation used in both files refers to the segments in clockwise order going in as-is conversion with sixteen segment displays.

![segmentMap]

#### Configuration
On boot, the seven GPIO for the configuration pads have their internal pullups enabled and are then set as inputs. They are all sampled. Any that have been bridged to ground will read as low and their inverted state can be used to set the configuration.

```c
  uint8_t config = 0x00;
  config |= !read(PIN_0) << 0;
  config |= !read(PIN_1) << 1;
  config |= !read(PIN_2) << 2;
  config |= !read(PIN_3) << 3;
  config |= !read(PIN_4) << 4;
  config |= !read(PIN_5) << 5;
  config |= !read(PIN_6) << 6;
```

The pads have functions attached to them, some are just switches, while others join together in a binary segment to allow multiple selections.

| Pad | Function         | Status               |
| ---:| ---------------- | -------------------- |
|   0 | Inverted Display | Not implemented      |
|   1 | Baud (Bit 3)     | Implemented in 0.6   |
|   2 | Baud (Bit 2)     | Implemented in 0.6   |
|   3 | Baud (Bit 1)     | Implemented in 0.6   |
|   4 | Baud (Bit 0)     | Open for Development |
|   5 | Pending          | Open for Development |
|   6 | Pending          | Open for Development |


##### Baud Selection
Pads `[4:1]` allow baud selection, the default is `115200` as it is a common bitrate that is available on most computer and microcontrollers and is reasonably fast for most applications.

| Pad 4 | Pad 3 | Pad 2 | Pad 1 | Selected Baud |
| -----:| -----:| -----:| -----:| -------------:|
|     0 |     0 |     0 |     0 |        115200 |
|     0 |     0 |     0 |     1 |           110 |
|     0 |     0 |     1 |     0 |           300 |
|     0 |     0 |     1 |     1 |           600 |
|     0 |     1 |     0 |     0 |          1200 |
|     0 |     1 |     0 |     1 |          2400 |
|     0 |     1 |     1 |     0 |          4800 |
|     0 |     1 |     1 |     1 |          9600 |
|     1 |     0 |     0 |     0 |         19200 |
|     1 |     0 |     0 |     1 |         38400 |
|     1 |     0 |     1 |     0 |         57600 |
|     1 |     0 |     1 |     1 |        128000 |
|     1 |     1 |     0 |     0 |        230400 |
|     1 |     1 |     0 |     1 |        256000 |
|     1 |     1 |     1 |     0 |        460800 |
|     1 |     1 |     1 |     1 |       1000000 |

It is tested with a 4 bit mask and right-shifted to get numbers 0-15 from the config byte.
```c
uint32_t bauds[16] = {115200, 110, /*...*/, 460800, 1000000};
uint32_t baud = bauds[(config & 0X1E) >> 1];
```

#### Compiling
It is setup to be compiled through [PlatformIO]. More information can be found through its [documentation][platformIODocs]. Changes may be made to the settings in the `ini` file.


#### Flashing
The [programming pads](#programming) on the back are used to program the module. An ST-Link V2 with the SWIM protocol is used to upload the firmware.

Uploading using PlatformIO is currently used. Refer to [documentaiton][platformIODocs]. Changes may be needed to the `ini` file settings.

We also use a custom bash script internally that uploads, tests, and updates our database. It uses STM8Flash on Linux machines and ST Visual Programmer on WSL.

## Absolute maximum ratings
**To be tested, don't have the power supply, or really the heart to kill a module just yet.**

Works fine down to 3.3V.

## Guaranteed ratings

| Mesurement   | Value | Unit | Tolerence |
| ------------ | -----:| ---- | --------- |
| Power Supply |   5.0 | V    | ± 0.2     |
| Max current  |   319 | mA   | ± 5%      |
| Max Temp     |    60 | C    |           |
| Min Temp     |   -20 | C    |           |

## Manufacturing
Designing for manufacturing was a large portion of this project. This was done through many approaches on a number of fronts.

### BOM
The BOM was selected with parts that are common to the Chinese high-volume manufacturing market, have strong supply chains, as well as many alternatives in case a supplier stops manufacture. The number of unique parts was kept to a minimum and the maximum amount of features can be implemented with "free" options, like SMD pads. The table of BOM is shown below.

| REF       | QTY | Manufacturer               | MPN              | Description                                 |
| --------- | ---:| -------------------------- | ---------------- | ------------------------------------------- |
| C1        |   1 | AVX                        | TAJB107K006RNJ   | CAP: Tantalum 100uF 6.3V CASE-B_3528        |
| C2        |   1 | AVX                        | TAJA106K016RNJ   | CAP: Tantalum 10uF 16V CASE-A_3216          |
| C3 C6     |   3 | Samsung Electro-Mechanics  | CL05A105KA5NQNC  | CAP: MLCC 1uF 25V 0402                      |
| C4 C5 C7  |   2 | Samsung Electro-Mechanics  | CL05B104KO5NNNC  | CAP: MLCC 100nF 16V 0402                    |
| D1-D128   | 128 | Hubei KENTO Elec           | KT-0603R         | LED: RED 520-625nM 90-100mcd@20mA 0603      |
| R1 R2     |   2 | Uniroyal Elec              | 0402WGF1002TCE   | RES: 10K 1% 1/16W 0402                      |
| U1        |   1 | STMicroelectronics         | STM8S003F3P6TR   | MCU: 8b 16Mhz 8k Flash 128B EEPROM TSSOP-20 |
| U2        |   1 | Shenzhen Titan Micro Elec  | TM1640           | DRV: 16x8 LED Driver SOP-28                 |

The [Octopart] BOM is also available, although not much use since the parts are not carried by US distributors.

### PCB-Assembly
The PCB assembly is single-sided surface mount components only. The smallest components are 0402. All can be PNP from tapes or tubes, and reflowed at once. There are three fiducials as well as three tooling holes on each board. The tooling holes are `1.152 mm` and the fiducials are `1.5 mm` x `3 mm`. There are 139 components all of which are SMD, yielding a total of 322 solder joints.

![assembly]

### Physical Assembly
The panels are combined in order and can be held together with `3 mm` x` 7.5 mm` nylon 6/6 push rivets. This makes ingress into inventory much faster, and gives the customer another option to use for mounting since it's an uncommon part.

### Production Scaling
The physical assembly varies in the volume of production. Further sections will be updated with information if we ever reach those volumes.

#### PCB Stack
First iteration is the PCB stack as that has no tooling cost and all can be order from the same manufacturer. There are four PCBs in the stack that make-up the display.

| Board | Height (mm) | Width (mm) | Layers | Copper  | Thickness (mm) | Material | Min Drill (mm) | Trace Sizing | Mask  | Silk   | E-Test |
| ----- | -----------:| ----------:| ------:| -------:| --------------:| -------- | --------------:| ------------:| ----- | ------ | ------ |
| L0    |      100.00 |      66.66 |      2 |  1.0 oz |            1.0 | FR4      |            0.3 |          6/6 | Green |  White | Yes    |
| L1    |      100.00 |      66.66 |      2 |  1.0 oz |            1.6 | FR4      |            N/A |          N/A | Black |  White | No     |
| L2    |      100.00 |      66.66 |      2 |  1.0 oz |            1.6 | FR4      |            N/A |          N/A | Black |  White | No     |
| L3    |      100.00 |      66.66 |      2 |  1.0 oz |            1.6 | FR4      |            N/A |          N/A | Black |  White | No     |


The bottom board is the electrical board containing all the components and signals, and is used for all iterations. The following two boards provide spacing and separation for the diffusion of the LEDs, as well as cut outs for the other components, and the final board provides diffusion and a solid panel for the front face. The layout of each layer is shown in the table below.

|   L0  |   L1  |   L2  |   L3  |
|:-----:|:-----:|:-----:|:-----:|
| ![L0] | ![L1] | ![L2] | ![L3] |

PCB stack is best for quantities below 500 units.

#### Die Cut
The die cut panels replace the top three panels with `1/16"` plastic that is die cut. This is faster to manufacture and less expensive, since we do not need the copper, silk, or mask layers. Also, uses a through-opaque material instead of the FR4 providing better protection from light bleed.

|     L1    |     L2    |     L3    |
|:---------:|:---------:|:---------:|
| ![L1-DIE] | ![L2-DIE] | ![L3-DIE] |

Switch to die cut at 1k-10k units.

#### Injection Moulding
Injection moulded panel will replace the front three panels with a single injection moulded plastic part, as well as the screws. Providing the option to either punch through from the front to get the same M3 holes, or screw in from the back to have a completely clean front panel. The IM part also provides other benefits, such as, a more consistent texture on the whole panel, and a high contrast front that has no discernible pattern when off.

![imProto]

A test model was made with 2.5 deg draft angles and `1.2 mm` wall thickness for ABS moulding. Approximate calculations show tooling costs of $7.5k for production steel tooling, and 15s cycle time.

Switch to IM at 20k-100k units.

#### Custom ASIC
Flipchip LEDs with COB fully integrated controller. HDL gateware design to begin at 50k units. RISC-V processor with 16x16 multiplexing LED array at a 72 MHz PLL clock.

[Hey, a girl can dream. Chip die image]

Engineering and silicon die cost around $50k tooling (maybe? I don't really know, but I could probably synthesize a sea of gates design that works) Switch to custom ASIC at 100k units.

### Programmer
The chip needs to be programmed with the firmware and tested for proper operation before sending out to customers. Two programmers are designed. First, a low cost simple programmer for smaller quantities and available on special request for those who want to customize the firmware, and the other is a completely independent production-ready programmer and tester.

#### Minimal
Them minimal program has holes for alignment corresponding to the top row, and four spring pins. These connect out to the programming header which can then be corrected to an ST-Link V2. The alignment holes have M3x8 screws and nuts which were added to create alignment pins. The board to be programmed is aligned with the pin and held down while programming.

![minimalProgrammer]

#### Production
The production programmer is a program and test jig. The boards are slipped under the bottom overhang and pushed down until the lever snaps and holds them in place. Then a full test suite can be run, checking the input and output, programming with multiple firmwares and reading back system outputs to verify that the device works properly.

![productionProgrammer]

### Artwork
The artwork on the back is a trademark and protected by copyright. This can not be duplicated on derivative works. It consists of the Kolibri bird, copyright and designer notices, certifications, a location for labeling, as well as the URL and QR code to documentation.

### Labels
The back has a location for a `38 mm` x `13 mm` label from a Brother `38 mm` continuous label. This label can have serial number, batch numbers, the model number, and any other device specific information.

![config-label]

### Inventory and QC
Inventory can then be managed with QR coded serialized tags. The serialization also provides better QC as it allows failure analysis and tracking in case of issues traceable to the batch and assembly level.

### Part Numbers
The manufacturer part number is based on the following scheme.

MPN: `SEG-16-AAA-BBBB`

Where `AAA` is the three character code for color

| Code   | Color              |
| ------ | ------------------ |
| `RED`  | Red                |
| `GRN`  | Green              |
| `BLU`  | Blue               |
| `RGB`  | Red Green Blue     |
| `WHT`  | White (5000k)      |
| `WWT`  | Warm White (3500k) |
| `YEL`  | Yellow             |

And `BBBB` denotes the face type

| Code   | Face Type                       |
| ------ | ------------------------------- |
| `NOON` | Noon face, Exposed FR4          |
| `MDNT` | Midnight face. Black soldermask |
| `PLEX` | Acrylic Laser Cut               |
| `IM  ` | Injection Moulded               |

## Safety
The assembly is almost exclusively made from FR4. It is highly fire retardant and will not burn after a flame is removed.

The edges are milled, but it is possible to have small pieces that could cause cuts, abrasions, or become embedded in the skin. If sanding or milling the board, use a respirator as fiberglass dust is carcinogenic.

The boards are assembled in a lead-free process and all components are RHOS certified.

The low voltage `3.0`-`5.5V` as well as the currents used pose very little risk to healthy humans.

## Certifications
Certifications take time and effort but will make a better product by guaranteeing its safety to users and let them use it in other projects. The table below shows the order we will be trying to obtain certifications.

| Cetrtifing Authority     | Status                    |
| -------------------------| ------------------------- |
| OSHW                     | [DE000087]                |
| CE                       | No  (Self Certification)  |
| FCC                      | No  (Self Certification)  |
| UL Registered Component  | No  (yearly fee)          |
| WEEE                     | No  (yearly fee)          |

## Licence
The product was designed by Sawaiz Syed for Kolibri who owns the copyright. Everything is released under permissive copyleft licenses, and copies of all licenses are included.

| Sector        | License      | Verison |
| ------------- | ------------ | -------:|
| Hardware      | [CERN-OHL-S] |     2.0 |
| Firmware      | [GNU GPL]    |     3.0 |
| Documentation | [CC BY-SA]   |     4.0 |

Copies of all licenses are required with the distribution of files. All files are available in easy-to-modify types for remixing. Please purchase original products from Kolibri to support further products, design, and research.

## Attribution
As with everything, this too is built on the gracious support of previous projects.

- KiCad
- Inkscape
- Blender
- SDCC
- STM8Flash
- PlatfromIO

### Fonts
- [DejaVu]
- [IBM Plex Mono]

### Libraries
- [Sixteen Segment ASCII](https://github.com/dmadison/LED-Segment-ASCII) - MIT - Copyright (c) 2017 David Madison
- STM8 SPL (Available component, but not included)

## Recommended Reading


## Todo
- [ ] Switch from SPL to just C and registers or [open headers](https://github.com/gicking/STM8_headers)
- [ ] Change from PlatformIO to a makefile
- [ ] Implement inverted font

<!-- Files -->
[KT-0603R]:               ./pcb/SEG-16-XXX-XXXX-L0/components/KT-0603R/KT-0603R.pdf
[TM1640]:                 ./pcb/SEG-16-XXX-XXXX-L0/components/TM1640/TM1640.pdf
[TM1640ENG]:              ./pcb/SEG-16-XXX-XXXX-L0/components/TM1640/TM1640-ENG.pdf
[STM8S003]:               ./pcb/SEG-16-XXX-XXXX-L0/components/STM8S003/STM8S003.pdf
[0472861001]:             ./pcb/SEG-16-XXX-XXXX-L0/components/0472861001/0472861001.pdf
[schematic.pdf]:          ./pcb/SEG-16-XXX-XXXX-L0/SEG-16-XXX-XXXX-L0.pdf
[segmentMapping.h]:       ./firmware/include/segmentMapping.h
[sixteenSegments.h]:      ./firmware/include/sixteenSegments.h

<!-- Links -->
[Octopart]:               https://octopart.com/bom-tool/6sdiCse8
[97161A128]:              https://www.mcmaster.com/97161A128
[91292A112]:              https://www.mcmaster.com/91292A112
[91828A211]:              https://www.mcmaster.com/91828A211
[90690A037]:              https://www.mcmaster.com/90690A037
[R3075]:                  https://www.amazon.com/gp/product/B07Z1XCS3M/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1
[Misumi HFS3]:            https://us.misumi-ec.com/vona2/detail/110300465870/
[Misumi HFS5]:            https://us.misumi-ec.com/vona2/detail/110302683830
[MakerBeam]:              https://www.makerbeam.com/makerbeam/makerbeam-10x10mm-profile-lengths-anodised-in-clea/
[Makerbeam XL]:           https://www.makerbeam.com/makerbeamxl/makerbeamxl-15x15mm-profile-lengths-anodised-in-cl/
[OpenBeam]:               https://www.makerbeam.com/openbeam/openbeam-15x15mm-profile-lengths-anodised-in-black/
[MicroRAX]:               http://www.microrax.com/
[Metric 8020]:            https://8020.net/20-2020.html
[STM8SPL]:                https://www.st.com/en/embedded-software/stsw-stm8069.html
[PlatformIO]:             https://platformio.org/
[platformIODocs]:         https://docs.platformio.org/en/latest/

<!-- Internal Links -->
[userGuide]:              ./docs/userGuide.md
[asciiCurrent]:           ./docs/asciiCurrent.md
[configTable]:            ./docs/configTable.md

<!-- Images -->
[SIXTEEN]:                ./docs/title/SIXTEEN.png                                               "SIXTEEN Rendered on display"
[SEGMENT]:                ./docs/title/SEGMENT.png                                               "SEGMENT Rendered on display"
[DISPLAY]:                ./docs/title/DISPLAY.png                                               "DISPLAY Rendered on display"
[isoArray]:               ./docs/product/isoArray.jpg                                            "Isometric view of a few panels lit with time"
[SEG-16-RED-NOON]:        ./docs/product/SEG-16-RED-NOON.jpg                                     "Top view of a NOON"
[SEG-16-RED-MDNT]:        ./docs/product/SEG-16-RED-MDNT.jpg                                     "Top view of a MDNT"
[SEG-16-RED-BASE]:        ./docs/product/SEG-16-RED-BASE.jpg                                     "Top view of a BASE"
[angledShow]:             ./docs/product/angledShow.jpg                                          "Angled shot of two panels"
[cycleGif]:               ./docs/char/char8M.gif                                                 "Animated gif of full ASCII cycle"
[schematic]:              ./docs/assembly/schematic.png                                          "Full schematic of design"

<!-- Config -->
[config-back]:            ./docs/config/backPanel.jpg                                            "View of entire back panel"
[config-pgrm]:            ./docs/config/pgrm.jpg                                                 "Detail of the program pads"
[config-dataflow]:        ./docs/config/dataflow.jpg                                             "Detail of the data flow connector and jumpers"
[config-dataflowInv]:     ./docs/config/dataflowInv.png                                          "Soldering instructions on traces to cut and bridge"
[config-config]:          ./docs/config/config.jpg                                               "Detail of configuration pads"
[config-keyed]:           ./docs/config/keyed.jpg                                                "Detail of keyed spring connector"
[config-label]:           ./docs/config/label.png                                                "Example of label"

<!-- Firmware -->
[TM1640Timing]:           ./docs/firmware/TM1640Timing.png                                       "Timing diagram of T1640 Protocol"
[dateCapFile]:            ./docs/firmware/fullDisplayCommand.sal                                 "Saleae logic analyzer file"
[dataCapImg]:             ./docs/firmware/dataCapImg.png                                         "Image of data capture"
[segmentMap]:             ./docs/firmware/segmentMap.png                                         "Letters to physical segment"

<!-- Mounting Options -->
[mountingDim]:            ./docs/mounting/mountingDim.png                                        "Dimensioned drawing of mounting holes and physical size"
[plasticRivet]:           ./docs/mounting/R3075.jpg                                              "Plastic rivet with ruler"
[rivetInstalled]:         ./docs/mounting/R3075mount.jpg                                         "Plastic rivet installed"
[2020Extrusion]:          ./docs/mounting/2020Extrusion.jpg                                      "20mm Aluminum Extrusion"
[2020Installed]:          ./docs/mounting/2020Installed.jpg                                      "Example of display mounted in 2020 extrusion"
[M3x8]:                   ./docs/mounting/M3x8.jpg                                               "M3x8 screw and nut"
[M3x8Installed]:          ./docs/mounting/M3x8Installed.jpg                                      "Module assembled with screw and nut"
[makerbeamParts]:         ./docs/mounting/makerbeamParts.jpg                                     "Parts for mounting on MakerBeam"
[makerbeamInstalled]:     ./docs/mounting/makerbeamInstalled.jpg                                 "Example installation on makerbeam"
[openbeamParts]:          ./docs/mounting/openbeamParts.jpg                                      "Parts for mounting on OpenBeam"
[openbeamInstalled]:      ./docs/mounting/openbeamInstalled.jpg                                  "Example installtion on OpenBeam"
[springPin]:              ./docs/mounting/springPin.jpg                                          "Spring pins with ruler"
[springPinInstalled]:     ./docs/mounting/springPinInstalled.jpg                                 "Example of spring pin installation"

<!-- Assembly -->
[assembly]:               ./docs/assembly/assembly.png                                           "Assembly diagram"
[L0]:                     ./docs/assembly/L0.png                                                 "Layer 0 layout"
[L1]:                     ./docs/assembly/L1.png                                                 "Layer 1 layout"
[L2]:                     ./docs/assembly/L2.png                                                 "Layer 2 layout"
[L3]:                     ./docs/assembly/L3.png                                                 "Layer 3 layout"
[L1-DIE]:                 ./docs/assembly/L1-DIE.png                                             "Layer 1 die cut outline"
[L2-DIE]:                 ./docs/assembly/L2-DIE.png                                             "Layer 2 die cut outline"
[L3-DIE]:                 ./docs/assembly/L3-DIE.png                                             "Layer 3 die cut outline"
[imProto]:                ./docs/assembly/imProto.png                                            "Prototype injection moulding model render"

<!-- Programmer -->
[minimalProgrammer]:       ./docs/programmer/minimalProgrammer.jpg                               "Minimal programmer picture"
[productionProgrammer]:    ./docs/programmer/productionProgrammer.png                            "Production programmer render"

<!-- Components -->
[IMG-KT-0603R]:           ./pcb/SEG-16-XXX-XXXX-L0/components/KT-0603R/KT-0603R.jpg              "Led componet image"
[IMG-TM1640]:             ./pcb/SEG-16-XXX-XXXX-L0/components/TM1640/TM1640.jpg                  "Led driver componet image"
[IMG-STM8S003]:           ./pcb/SEG-16-XXX-XXXX-L0/components/STM8S003/STM8S003.jpg              "Microcontorller part image"
[IMG-TAJA106K016RNJ]:     ./pcb/SEG-16-XXX-XXXX-L0/components/TAJA106K016RNJ/TAJA106K016RNJ.jpg  "Bulk capacitor image"
[IMG-TAJB107K006RNJ]:     ./pcb/SEG-16-XXX-XXXX-L0/components/TAJB107K006RNJ/TAJB107K006RNJ.jpg  "Bulk capacitor image"

<!-- Certifications -->
[DE000087]:               https://certification.oshwa.org/DE000087.html

<!-- Licence -->
[CERN-OHL-S]:             ./pcb/LICENSE
[GNU GPL]:                ./firmware/LICENSE
[CC BY-SA]:               ./docs/LICENSE

<!-- Attribution -->
[DejaVu]:                 https://dejavu-fonts.github.io/
[IBM Plex Mono]:          https://www.ibm.com/plex/
