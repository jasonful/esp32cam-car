
# ESP32 RobotCam


The ESP32 robot cam is a mobile surveillance robot that can be controlled over the internet.  It is built around a standard ESP32-Cam board, plus a motor driver, battery, power supply board, and motorized platform.  It also includes an optional inductive charger so that it can "dock" and recharge itself while remaining connected to the internet and ready to respond to commands without depleting its battery.

## The hardware
1. [ESP32-Cam] (AI-Thinker, or clone)
	The one I bought from [BangGood](https://www.banggood.com/ESP32-CAM-WiFi-+-bluetooth-Camera-Module-Development-Board-ESP32-With-Camera-Module-OV2640-p-1394679.html?rmmds=myorder&cur_warehouse=USA) was configured to use an external antenna, whereas the one from [Amazon](https://www.amazon.com/gp/product/B07WCFGMTF/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) used the internal antenna.  Both work, and you can switch a board from one to the other, though it requires some delicate [desoldering and resoldering](https://randomnerdtutorials.com/esp32-cam-connect-external-antenna/).
2. [AdaFruit PowerBoost 500](https://www.adafruit.com/product/1944)
3. [DRV883 Motor Driver](https://www.amazon.com/gp/product/B07FZY8GX2/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
4. LiPoly battery, such as [this one](https://www.adafruit.com/product/328)
1. 4 AA Batteries
5. Half-size breadboard
6. Robot chassis, such as [this one](https://www.aliexpress.com/item/32811461741.html?spm=a2g0o.productlist.0.0.15802be5VlgLzG&algo_pvid=0c694e40-f457-493e-bc05-ba8251292493&algo_expid=0c694e40-f457-493e-bc05-ba8251292493-2&btsid=0bb0622916094382362498562e15be&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_) or search for "2WD Motor Smart Robot Car Chassis" on [Aliexpress](https://aliexpress.com).
7. [Variable potentiometer](https://www.sparkfun.com/products/9806) (optional, for reporting charging status on the web page)
8. [Inductive charger](https://www.amazon.com/gp/product/B07XC23LS2/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) (optional)
9. Male to male Dupont wires, or other breadboard wires

##Tools
1. FTDI board, such as [this](https://www.adafruit.com/product/284) or [this](https://www.tindie.com/products/kdcircuits/ftdi-usb-serial-converter-5v33v/) or [this](https://www.aliexpress.com/item/32519490747.html)
1. Hot glue gun, or adhesive strips, or adhesive Velcro strips

## Assembly
1. Assemble the robot chassis according to the instructions that come with it.  The instructions that came with mine were pretty incomprehensible, but it's not that hard to figure out how to put it together even without instructions.
2. Solder headers onto the Esp32-Cam, the PowerBoost, and the Motor Driver.  Plug all three into the breadboard with the PowerBoost at the top, Motor Driver in the middle, then the variable potentiometer, then the ESP32-Cam at the bottom.  On a half-size breadboard, there are just barely enough rows to fit everything. The camera lens will be pointing up at the ceiling so you'll want to flex it 90 degrees so it is pointing forward; I put a cube of [poster tack](https://www.amazon.com/Elmers-Poster-Tack-Reusable-Ounces/dp/B000BKQDB4#:~:text=Hang%20maps%2C%20posters%2C%20paper%20decorations%2C%20and%20other%20lightweight%20items,and%20other%20non%2Dporous%20surfaces.) behind it to hold it up.
3. Attach breadboard to car chassis, towards the front, with camera facing forward, using hot glue or adhesive strips.

## Wiring

![Wiring](https://raw.githubusercontent.com/jasonful/esp32cam-car/master/wiring.png)


ESP32-Cam|PowerBoost|Motor Driver| Var. Pot.|AA Batt Pack|Left Motor|Right Motor
---------|--------------|--------|----------|------------|----------|-----
5V		|5V
Gnd		|Gnd
Io12	|				|In4
Io13	|				|In1
Io15	|LB
Io14	|				|		| 2 (middle)
Io2		|				|In3
Io14	|				|In2	|			|			|
		|				|VCC	|			|+
		|				|Gnd	|			|-
		|5V				|EEP
		|				|Out1	|			|			|+ (top)
		|				|Out2	|			|			|- (bottom)
		|				|Out3	|			|			|			|- (bottom)	
		|				|Out4	|			|			|			|+ (top)
		|USB			|		|1 (left)			
		|Gnd			|		|3 (right)	
		
		
You may also want to put a [pushbutton](https://www.sparkfun.com/products/97) between the PowerBoost's EN and GND to make resetting easier.  Or just have a dangling DuPont wire hanging off EN that you can plug into GND.

## Software
If you are not already familiar with how to use the Arduino IDE to upload code to an Esp32-Cam, see [this tutorial](https://randomnerdtutorials.com/program-upload-code-esp32-cam/#:~:text=The%20ESP32%2DCAM%20AI%2DThinker%20module%20is%20an%20ESP32%20development,your%20computer%20and%20upload%20code.)
The code is available at [TBD](https://github.com/jasonful/robotcar).