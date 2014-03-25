## NFC_Tag_M24LR6E

This is an Arduino library to use M24LR6E as a NFC Tag.

### Features

##### *I2C interface* #####
+ Two-wire I2C Serial interface supports 400KHZ protocol
+ Single supply voltage: 1.8V ~ 5.5V
+ Byte and Page Write(up to 4 bytes)
+ Random and Sequential read modes
+ Self-timed programming cycle
+ Automatic address incrementing

##### *Contactless interface* #####
+ ISO 15693 and ISO 18000-3 mode 1 compatible
+ 13.56 MHz ± 7 kHz carrier frequency
+ To tag: 10% or 100% ASK modulation using 1/4 (26Kbit/s) or 1/256 (1.6 Kbit/s) pulse position coding
+ From tag: load modulation using Manchester coding with 423 kHz and 484 kHz subcarriers in low (6.6 kbit/s) or high (26 kbit/s) data rate mode. Supports the 53 kbit/s data rate with Fast commands
+ Internal tuning capacitance: 27.5 pF
+ 64-bit unique identifier (UID)
+ Read Block & Write (32-bit blocks)

##### *Memory* #####
+ 64-Kbit EEPROM organized into:
 1. 8192 bytes in I2C mode
 2. 2048 blocks of 32 bits in RF mode 
+ Write time
 1. I2C: 5ms(max)
 2. RF: 5.75 ms including the internal Verify time
+ More than 1 million write cycles
+ More than 40-year data retention
+ Multiple password protection in RF mode
+ Single password protection in I2C mode


### Getting Started
please follow the example sketch( **LedControl** ) and you can find some userful things in resources directory. Have fun!


----

This software is written by lawliet ([wei.zou@seeedstudio.com](wei.zou@seeedstudio.com "wei.zou@seeedstudio.com")) for seeed studio<br>
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.<br>

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>

[![Analytics](https://ga-beacon.appspot.com/UA-46589105-3/NFC_Tag_M24LR6E)](https://github.com/igrigorik/ga-beacon)
