# SolderDuino
Arduino shield soldering station for Weller RT/RTM tips with 0.96" OLED display
![alt text](https://github.com/VSElec/SolderDuino/blob/master/DOC/SolderDuinoPCB%20(1).JPG?raw=true)

As an electronics enthusiast I am fortunate to work in the electronics field and I have started welding the first components with a soldering station from Weller.
By developing electronics projects even at home, the expense of a soldering station like that of Weller is not justified so following various projects of other soldering stations I have built myself.
I opted to make a shield that adapts to Arduino for simplicity and cost.

**Features:**
-	Measurement of the input voltage;
-	Rotary encoder for menu and temperature management;
-	Oled display 0.96” SPI;
-	Screw terminal blocks for easy insertion of cables;
-	Cold junction compensation by NTC;
-	OPAMP with low offset voltage for better thermocouple acquisition;
-	Current measurement by shunt resistance;
-	Automatic shutdown with the possibility of setting the time;
-	PID regulation;
-	Personalized settings; 
-	Save in eeprom of temperatures, PID and shutdown time;
-	rotection for low voltage, high temperature, polarity inversion and tip not connected.

**Specifications:**
-	Supply voltage range: 12V ÷ 13V (if it drops below 11 volts the PWM is turned off);
-	Current: 12V 6A peak;
-	IDLE Current: <10mA;
-	Temperature set: 0°C ÷ 450°C;
-	Heating speed: 50°C to 350°C about 5sec.
