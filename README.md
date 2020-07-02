# Z80-MBC
Here are all the project files (SW & HW) of the Z80-MBC, a complete mini Z80 system with 64kB RAM, Basic and Forth interpreters, CP/M 2.2, QP/M 2.71, Assembler and C toolchains, Serial port, an User led and key.

The complete project with all the details is published here: https://hackaday.io/project/19000-a-4-4ics-z80-homemade-computer-on-breadboard

The PCB gerber files are here: https://github.com/WestfW/4chipZ80 (the PCB was designed by Bill Westfield).





** UPDATE February 2018 **

New version S221116_R100218_Z80.ino. Fix the "ghost RTC" bug: when there isn't any Virtual Disk (only Basic and Forth) the RTC clock was always incorrectly found (More info here: https://hackaday.io/project/19000/log/89392-bug-fix-the-ghost-rtc).

GNR version
These are my changes:
1) Slight reorganization of init code
2) Change of address for I/O board (https://smile.amazon.com/gp/product/B07P2H1NZG)
3) Support for piggyback EEPROM (4 drives) in Arduino code
4) Patcher to patch up existing BIOS to let CP/M use the 4 drives
5) Serial input status on Input 0 -- note that the user switch is now bit 7. Also note bit 0 doesn't
really reflect the transmitter status, but I should probably fix that.

To add the 3rd and 4th drives take new 1025 EEPROMs and do the following:
a) Remove drive B
b) Insert new EEPROM and power up board to iLoad mode
c) Load iDisk
d) Setup disk from a drive B image (e.g., the Turbo Pascal image from the disk pack)
e) Remove drive B and repeat for the 4th EEPROM
f) Power down 
g) Replace original B drive
h) Lift up pin 2 of each new EEPROM
i) Using small piece of wire, short pin 2 to pin 3
j) Piggyback the new EEPROMs over the old ones (one on top of each old EEPROM). Make sure pin 2 does not touch.

If you are unsure, you can squeeze the ICs so the pins will grip the main EEPROMs pretty well and test. Once working you may want to solder them to each other.

Note: You won't see the drives until you patch the BIOS (see PATCH1.BAS or one of the other patch methods) or use a rebuilt BIOS.


Coming soon... rebuild BIOS for 4 drives

If you are interested in PCPUT and PCGET using this firmware, see this document: https://docs.google.com/document/d/1xUM6nIeuzou1vhWvedSDNuM72x5ku1T-htuIr2hJKac/edit?usp=sharing 
Note that changing the INO file is not needed in this case if you are using the one in this repo.


