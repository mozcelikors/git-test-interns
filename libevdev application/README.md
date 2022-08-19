**Setting up a GPIO-Button on a Raspberry Pi using libevdev**

Event device is a generic input event interface in the Linux kernel. It generalizes raw input events from device drivers and makes them available through character devices in the /dev/input/ directory.
The user-space library for the kernel component evdev is called libevdev. Libevdev abstracts the evdev ioctls through type-safe interfaces and provides functions to change the appearance of the device. 

To inspect them I would recommend the installation of the evtest and input-utils packages on Debian/Ubuntu based distributions. The lsinput command (run as root) shows which ones are available on a system.

    sudo apt-get install evtest
    sudo apt-get install input-utils

The missing link between the gpio-keys driver and the setup of the actual GPIO ports, where the buttons are connected to, is a so called device-tree (DT) overlay.

While DT itself is a data structure for describing hardware, a DT overlay is something a user can put in place to change such a hardware description in a way which matches the actual application scenario (like buttons, buses etc. connected to the device).

So let’s build such an overlay for the button shown in our schematic above.

    /dts-v1/;
    /plugin/;
    / {
       compatible = "brcm,bcm2835", "brcm,bcm2708", "brcm,bcm2709";
       
       fragment@0 {
          target-path = "/";
          __overlay__ {
             keypad: breadboard_keys {
                compatible = "gpio-keys";
                #address-cells = <1>;
                #size-cells = <0>;
    	        autorepeat;
                
                button@23 {
                   label = "breadboard enter";
                   linux,code = <28>;
                   gpios = <&gpio 23 1>;
                };
             };
          };
       };
    };

Our overlay fragment contains a keypad called breadboard_keys. This is actually the string which lsinput will show as the actual name of our input device. gpio 23 is the GPIO port number on Raspberry Pi and, "1" is gpio definition of active low for button. Now, we save the above code in a **breadboard.dts** file. Then compile a binary version:

```dtc -I dts -O dtb -o /boot/overlays/breadboard.dtbo```

Finally, the following line must be added to the bottom line of /boot/config.txt:

```dtoverlay=breadboard```

You can see the button device you created with **lsinput** and test your button with the **sudo evtest** command.


In the second stage, we create own sudo evdev command using libevdev library. **libevdev** is a library for handling evdev kernel devices. It abstracts the evdev ioctls through type-safe interfaces and provides functions to change the appearance of the device.

```sudo apt-get install libevdev-dev```

After the installed libevdev library, we can run the breadboard.c file with below command line:

```gcc -I/usr/include/libevdev-1.0/ -march=native -Wall -o breadboard breadboard.c -levdev```

The second option to run is Makefile. Go to the file directory you downloaded.

```make```

Run the command and build the file. It is then executed with **./breadboard**. So you will get the same output as sudo evtest command.
