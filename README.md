# Z80-MBC
Here are all the project files (SW & HW) of the Z80-MBC, a complete mini Z80 system with 64kB RAM, Basic and Forth interpreters, CP/M 2.2, QP/M 2.71, Assembler and C toolchains, Serial port, an User led and key.

The complete project with all the details is published here: https://hackaday.io/project/19000-a-4-4ics-z80-homemade-computer-on-breadboard

The PCB gerber files are here: https://github.com/WestfW/4chipZ80 (the PCB was designed by Bill Westfield).





** UPDATE February 2018**

New version S221116_R100218_Z80.ino. Fix the "ghost RTC" bug: when there isn't any Virtual Disk (only Basic and Forth) the RTC clock was always incorrectly found (More info here: https://hackaday.io/project/19000/log/89392-bug-fix-the-ghost-rtc).

GNR version
===========

These are my changes (July 4-9, 2020):
1) Slight reorganization of init code
2) Change of address for I/O board (https://smile.amazon.com/gp/product/B07P2H1NZG)
3) Support for piggyback EEPROM (4 drives) in Arduino code
4) Patcher to patch up existing BIOS to let CP/M use the 4 drives
5) Serial input status on Input 0* note that the user switch is now bit 7. Also note bit 0 doesn't
really reflect the transmitter status, but I should probably fix that.
6) idisk can now compile for CP/M or iLoad mode (compile with zcc -O1 -D_CPM idisk.c -o idisk.com
7) Added format program to format a disk (use /S option to copy System from Drive A: to make a new system disk). Note: With the Format program you can skip
all the iDisk steps for adding a 3rd and 4th drive. Just start at step H and after restart you can format your new drives. For example "format 2" to format a new drive C.
8) Added a menu item to swap drive A/D for testing new system disks. Note: If D is formatted as a system disk it won't be readable. When you swap, the old A disk will be at D
   and also unreadable.
9) Added patchers to treat drive D a system disk or a data disk at run time (dsys or ddata). NOTE: This must be used with the matching CP/M image as it knows an exact address to patch and has no
   checking. See How To below, for more.
10) Updated CP/M (R090720) for better drive change handling and to automatically search drive A (current user) for COM files not found on current disk   
11) Updated CP/M (R100720) to allow search drive to change using PATH.COM (default A; can turn off search).

To add the 3rd and 4th drives take new 1025 EEPROMs and do the following:

a) Remove drive B

b) Insert new EEPROM and power up board to iLoad mode

c) Load iDisk

d) Setup disk from a drive B image (e.g., the Turbo Pascal image from the disk pack or the WordStar image)

e) Remove drive B and repeat for the 4th EEPROM

f) Power down 

g) Replace original B drive

h) Lift up pin 2 of each new EEPROM

i) Using small piece of wire, short pin 2 to pin 3

j) Piggyback the new EEPROMs over the old ones (one on top of each old EEPROM). Make sure pin 2 does not touch.

If you are unsure, you can squeeze the ICs so the pins will grip the main EEPROMs pretty well and test. Once working you may want to solder them to each other. See this photo for how they press fit: ![Piggyback DIPs](https://drive.google.com/file/d/1G_YWSm-YIfJ7HFxRcD5EgXIeHl-Vdnr_/view?usp=sharing) -- Apparently GitHub doesn't like Google links like this so: https://photos.google.com/photo/AF1QipO3HcaTiTKJVTq6BJv_xK0qFeHDZbAKy3ra5OhA

Note: You won't see the drives until you patch the BIOS (see PATCH1.BAS or one of the other patch methods) or use the rebuilt CP/M image.

You don't need the patch if you are willing to load a new CP/M System + Bios. To do this, load the hex file in CPM22SYS_BIOS_S050217_R040720.zip using iDisk just like any other disk image.
Note: This is just the system tracks, so you should not bother your data plus you must have an already formatted A disk to do this. If you want to rebuild the 
BIOS using TASM, note that you have to build CPM22 and that file includes the BIOS. You can't build only the BIOS.


If you are interested in PCPUT and PCGET using this firmware, see this document: [Google Doc](https://docs.google.com/document/d/1xUM6nIeuzou1vhWvedSDNuM72x5ku1T-htuIr2hJKac/edit?usp=sharing)
Note that changing the INO file is not needed in this case if you are using the one in this repo.

GNR Files of interest:
======================
* S221116_R040720_Z80.ino - Firmware including serial port patches and 4 disk support (NOTE: I/O port address and User button bit changes also)
* S221116_R050720_Z80.ino - Same as above but with option for swapping drive A/D
* newcpm/ - CP/M and BIOS built for 4 drives (also see CPM22SYS_BIOS_S050217_R040720.zip) : note R080720 adds several things (see below) and R090720 makes further improvements
* patch - Basic program to patch old BIOS for 4 drives (not needed with new cpm)
* D1_WORDSTAR.ZIP - Wordstar installed for Drive B ready of iDisk. Eats up most of the disk, so 4 drives recommended!
* iDisk - S250317 R040720.c  - iDisk patched for 4 drives
* iDisk - S250317.R040720.hex - Image for idisk4
* iDisk - S250317 R050720.c  - iDisk patched for 4 drives and compilable for use under CP/M; allows retarget of drives
* iDisk - S250317.R050720.hex - Image for idisk4 (above)
* idisk4.com - CP/M executable for above
* getput/ - Patched versions of pcput and pcget for use with modified firmware (works with original CP/M Bios, but needs new Arduino firmware)
* diskdump/ - Program to dump disk from CP/M (see How To, below)
* format.c - Source code for format program
* format.com - Format binary (Format drive_number [/S] [label] where drive_number is 0 to 3; note that drive 0 has S option by default)
* tools/buildcpm - Script for helping to build CPM under Linux
* path.com - Set Path for CPM R100720 or later (one drive; use @ to turn off search)

CP/M Changes:
=============
* R040720 - Added support for 4 drives
* R080720 - Made drives removable, autodetect system drives vs data drives, removed sector translation table
* R090720 - Improved drive change logic, search drive A (current user) if COM file not found on current drive 
* R100720 - PATH.COM can change search drive or turn off search; fixed a memory issue when adding lots of drives

How To
======
Things to know:

1) To load a disk image:
   * Boot while holding user
   * Select iLoad
   * Load iDisk4.hex
   * Follow prompts to send HEX files
   * Easiest to set small delays on terminal character/line and paste into terminal for both hex files

2) To prepare iLoad Hex files from C program:

  sdcc -mz80 xxx.c -o xxx.hex

3) To prepare CP/M com file with z88dk:

  zcc +cpm -lm -o xxx.com xxx.c

4) To build ASM hex images:

  wine tasm [options] xxx.asm xxx.hex
  
  (Example: wine tasm -s -h -c -g0 -80 cpm22.asm cpm22.hex)

5) To rebase hex file to 0 (for system track init using iDisk4):

  srec_cat xxx.obj intel offset -0xNNNN -o xxx0.hex intel
  
  (where NNNN is your start address)

6) To dump a disk from CP/M
   * Run dumpdisk.com supply drive # on command line (0-3)
   * When prompted start your terminal capture and press Epnter
   * When done, turn off capture
   * Open capture file in editor and split marked sections
   * Note: First record tells you the disk and can be changed:
     * :00000009F7 - Drive 0
     * :00000109F6 - Drive 1
     * :00000209F5 - Drive 2
     * :00000309F4 - Drive 3
     * You can reload those images using procedure #1 above
  
7) To XMODEM files to/from box

   * pcput filename.ext
   * pcget filename.ext
   
8) Upgrade CP/M
   * Use idisk4 or the idisk procedure (#1 above) to load a hex file from newcpm folder

9) Experiment with an alternate boot disk
   * Make sure drive D is empty or you don't care about it
   * format 3 /s system2     (or whatever label you like)
   * At this point, drive D will be unreadable because CP/M thinks it is a data format disk but it isn't (unless using R080720 CP/M)
   * Run dsys.com (ONLY IF USING R050720)
   * Now drive D will be readable
   * Copy files over to drive D that you want on your new boot disk - This could include overwriting the system tracks with a new version of CP/M or other OS
   * Reboot with User button down (requires R050720 Firmware)
   * Select option to swap disk 0 and 3
   * System will now boot off disk 3 which will be A
   * Now drive 0 is D (was A) and is unreabled for the same reason (unless using R080720 CP/M)
   * Run dsys to be able to use drive 0 (as D:)  (ONLY IF USING R050720)
   * Run ddata to restore drive D to using the data disk format (ONLY IF USING R050720)
   * Cold reboot (user button) to reverse the A/D swap
   * IMPORTANT: CP/M R080720 does NOT need dsys and ddata and you should NOT run them with any version except R050720. I will be moving these out of the main folders
   
10) Stress test I2C bus
   * Start with blank disk in D:
   * pip d:=a:*.*
   * Test the executables on D to ensure they work -- be sure to test several
   * This appears to stress the bus enough to fail when less traffic will work

Errata
======
   * None





