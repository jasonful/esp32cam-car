
# ESP32 RobotCam


The ESP32 robot cam is a mobile surveillance robot that can be controlled over the internet.  It is built around a standard ESP32-Cam board, plus a motor driver, batteries, power supply board, and motorized platform.  It also includes an optional inductive charger so that it can "dock" and recharge itself while remaining connected to the internet and ready to respond to commands without depleting its battery.

## Hardware
1. [ESP32-Cam] (AI-Thinker, or clone)
	The one I bought from [BangGood](https://www.banggood.com/ESP32-CAM-WiFi-+-bluetooth-Camera-Module-Development-Board-ESP32-With-Camera-Module-OV2640-p-1394679.html?rmmds=myorder&cur_warehouse=USA) was configured to use an external antenna, whereas the one from [Amazon](https://www.amazon.com/gp/product/B07WCFGMTF/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) used the internal antenna.  Both work, and you can switch a board from one to the other, though it requires some delicate [desoldering and resoldering](https://randomnerdtutorials.com/esp32-cam-connect-external-antenna/).  If you need an external antenna, get one with a "U.FL Mini PCI" connector.
2. [AdaFruit PowerBoost 500](https://www.adafruit.com/product/1944)
3. [DRV883 Motor Driver](https://www.amazon.com/gp/product/B07FZY8GX2/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
4. LiPoly battery, such as [this one](https://www.adafruit.com/product/328)
1. 4 AA Batteries
5. Half-size breadboard
6. Robot chassis, such as [this one](https://www.aliexpress.com/item/32811461741.html?spm=a2g0o.productlist.0.0.15802be5VlgLzG&algo_pvid=0c694e40-f457-493e-bc05-ba8251292493&algo_expid=0c694e40-f457-493e-bc05-ba8251292493-2&btsid=0bb0622916094382362498562e15be&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_) or search for "2WD Motor Smart Robot Car Chassis" on [Aliexpress](https://aliexpress.com).
7. [Variable potentiometer](https://www.sparkfun.com/products/9806) (optional, for reporting charging status on the web page)
8. [Inductive charger](https://www.amazon.com/gp/product/B07XC23LS2/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) (optional)
9. Male to male Dupont wires, or other breadboard wires

## Tools
1. FTDI board, such as [this](https://www.adafruit.com/product/284) or [this](https://www.tindie.com/products/kdcircuits/ftdi-usb-serial-converter-5v33v/) or [this](https://www.aliexpress.com/item/32519490747.html)
1. Hot glue gun, or adhesive strips, or adhesive Velcro strips

## Assembly
1. Assemble the robot chassis according to the instructions that come with it.  The instructions that came with mine were pretty incomprehensible, but it's not that hard to figure out how to put it together even without instructions.
2. Solder headers onto the Esp32-Cam, the PowerBoost, and the Motor Driver.  
1. If using an external antenna, (and assuming it is like [mine](antenna.jpg)) unscrew the two halves, drill a 1/4" hole in a convenient spot in the chassis, feed the body of the antenna through the top, then screw in the other half from below, and secure with the nut.  Attach the wire to the underside of the ESP32-Cam.
1. Plug the Esp32-Cam, the PowerBoost, and the Motor Driver into the breadboard with the PowerBoost at the top, Motor Driver in the middle, then the variable potentiometer, then the ESP32-Cam at the bottom.  On a half-size breadboard, there are just barely enough rows to fit everything. The camera lens will be pointing up at the ceiling so you'll want to flex it 90 degrees so it is pointing forward; I put a cube of [poster tack](https://www.amazon.com/Elmers-Poster-Tack-Reusable-Ounces/dp/B000BKQDB4#:~:text=Hang%20maps%2C%20posters%2C%20paper%20decorations%2C%20and%20other%20lightweight%20items,and%20other%20non%2Dporous%20surfaces.) behind it to hold it up.
3. Attach breadboard to car chassis, towards the front, with camera facing forward, using hot glue or adhesive strips.
4. Plug the Li-poly battery into the PowerBoost.  Important: Make sure the polarity of the battery matches the polarity of the PowerBoost; otherwise, you will destroy both. If you buy your battery from Adafruit, it will match.  But if purchased elsewhere, it very well may be reversed.  If you need to reverse the polarity, see [this video](https://www.youtube.com/watch?v=PYPZA9xxinU).  
1. Use an adhesive strip to mount the inductive charger (the half with the oval copper coil) to the front of the top of the chassis so that the coil hangs over the front of the chassis like a bumper. See [photo](front.jpg).
1. Tape the other half of the inductive charger to a wall, at a height where it aligns with the half on the chassis. See [photo](dock.jpg).  Attach USB power.
1. Insert 4 AA batteries into the holder.
1. Plug a USB cable from your PC to the FTDI board.  Connect the FTDI's TX to the ESP32-Cam's RX, and the FTDI's RX to the ESP32-Cam's TX, and Gnd to Gnd. (The FTDI does not need to supply power because that will come from the PowerBoost.)
1. Now wire up everything:

ESP32-Cam|PowerBoost|Motor Driver| Var. Pot.|AA Batt Pack|Left Motor|Right Motor|Ind. Charger
---------|--------------|--------|----------|------------|----------|-----------|----
5V		|5V				|EEP
Gnd		|Gnd			|Gnd	|3 (right)	|-			|			|			|-
Io12	|				|In4
Io13	|				|In1
Io15	|LB
Io14	|				|		|2 (middle)
Io2		|				|In3
Io14	|				|In2	|			|			|
.		|				|VCC	|			|+
.		|				|Out1	|			|			|+ (top)
.		|				|Out2	|			|			|- (bottom)
.		|				|Out3	|			|			|			|- (bottom)	
.		|				|Out4	|			|			|			|+ (top)
.		|USB			|		|1 (left)	|			|			|			|+		

		

Most of the wiring is just plugging wires into the breadboard, but you'll probably want to solder the wires to the [motor terminals](motor.jpg).  And solder the AA battery pack wires to header pins to make them easier to insert into the breadboard.  Same with the inductive charger [wires](charger.jpg).
I used the breadboard rails for USB and GND.  For the 5V I just used the holes next to the PowerBoost 5V.

### Optional:

1. You may want to put a [pushbutton](https://www.sparkfun.com/products/97) between the PowerBoost's EN and GND to make resetting easier.  Or just have a dangling Dupont wire hanging off EN that you can plug into GND (also useful for turning off the power when robot is not in use).  Or both.
2. You may want to connect the Motor Driver's EEP to GND temporarily.  This will disable the motors until you are ready to actually use the robot, thereby preventing the robot from accidentally flying off your desk, or pulling out FTDI wires or whatever.


## Software
1. If you are not already familiar with how to use the Arduino IDE to upload code to an Esp32-Cam, see [this tutorial](https://randomnerdtutorials.com/program-upload-code-esp32-cam/#:~:text=The%20ESP32%2DCAM%20AI%2DThinker%20module%20is%20an%20ESP32%20development,your%20computer%20and%20upload%20code.).
1. The sketch is available on [https://github.com/jasonful/esp32cam-car](https://github.com/jasonful/esp32cam-car).  It is based on [this](https://github.com/heets-silver/esp32cam-car) sketch by [Hyuk Kang](https://www.youtube.com/channel/UCLKgE95vZf-u6e4bhOaKAhQ).
2. Open the sketch in the Arduino IDE.  Enter your SSID and password into esp32cam-car.ino.  Under the Tools/Board menu choose "AI Thinker ESP32-CAM".  Under Tools/Port choose the port corresponding to the FTDI.
3. Upload the sketch and open the Serial Monitor (115200 baud).
4. Disconnect Io0 from GND, and reset (by momentarily pulling PowerBoost's EN to GND, or pressing the button if you installed one).


## Usage
1. The ESP32-Cam's LED will blink once when the camera is initialized correctly, and then twice when WiFi is connected.  It will blink 3 times if camera initialization fails, and then reboot.  (This happened to me sporadically.)
1. In the Serial monitor, you will see the address of the robot's web page.  You may want to go into your router's settings and permanently assign that IP address to your ESP32, so you never have to hook up the serial monitor again.
1. Disconnect the FTDI from the ESP32.
1. Is you disabled the motors, connect EEP to 5V now.
1. Open the robot's web page, and you should see a streaming video and a set of buttons to control the robot.  You should be able to now drive your robot from the web page.  The go/back/left/right buttons take effect as long as they are held down.  The smaller buttons outside those are the "nudge" buttons: They take effect for 100 milliseconds, and are useful for nudging the robot just a little bit.
1. To recharge the robot, drive it over to the spot on the wall where you mounted the other half of the inductive charger.  It might be difficult to get it perfectly aligned.  Note you have to manually refresh the web page to see the "Charging" show up.  You might want to manually align the two halves, then see what the camera sees, so you can try to duplicate that view in the future.  NOTE: While this is an interesting proof of concept for remote charging, I do not recommend actually leaving the robot unattended while charging, because I do not want anyone to burn their house down.

## Notes
### Calibrating the charge level
To detect when the battery is charging, there is a connection from the PowerBoost's USB pin to an input pin on the ESP32.  When the input pin reads HIGH, the web page will say "Charging" on the bottom left.  I would have expected this pin to be at 0V when not charging, but for some reason there is a small voltage, roughly 1.0 to 1.7V which is enough to register as HIGH.  So the variable potentiometer divides this voltage to a lower level that registers as LOW on the input pin.  To calibrate this, rotate the potentiometer to a point where the web page will say "Charging" when a USB power cable is plugged into the PowerBoost, and not say "Charging" when not plugged in.
### Accessing from the internet
By default, the robot's web page is only accessible from your local network.  To access it from a remote location over the internet, you will need to set up a VPN to tunnel into your local network.  Or you can set up [port forwarding](https://en.wikipedia.org/wiki/Port_forwarding) on your router, but if you don't want any random person on the internet controlling your robot, you will need to add authentication.
### Brownouts
If your ESP32-Cam often says "Brownout trigger detected" on boot, it could be caused by any [number](https://github.com/nkolban/esp32-snippets/issues/168) of power-related problems.  For me, it was poor wire connections on the breadboard.
### Design variations
The variable potentiometer is optional; it is there just so the web page can tell you when the robot is charging, i.e., when the robot is "docked" correctly to the inductive charger.  But if you are not using the inductive charger, or not operating the robot remotely, you probably don't need it.

I used separate batteries for the ESP32 and for the motors.  Theoretically, you could use one power source for both, but since the ESP32-Cam is so finicky about its power supply, I didn't risk it.  But if you use a different 5V supply, and you don't care about charging it remotely, you could even get rid of the PowerBoost board entirely.

Other models of motor driver should certainly work.
### Motors on startup
When the ESP32 boots, the left motor turns on (reverse) for a fraction of a second, which can be bad if the robot is on a desk or nearby something.  I tried various solutions but was unable to fix this, so if anyone verifies a solution, let me know...
### Charging
As mentioned above, I do not actually recommend leaving the robot unattended while charging, as these are handmade robots, not UL Listed, and I do not want to be responsible for any fires.
### Bugs
If you find any bugs in the code, the design, or this documentation, please log an issue on [github](https://github.com/jasonful/esp32cam-car/issues).