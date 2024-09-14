# RGB fixer

*As later discovered while developing the main device's LCD interface, [using this website](https://www.online-utility.org/image/convert/to/XBM) to convert images to the TFT library's format may cause the images to be flipped.*

*As inverting bits is not an easy task, this tool helps with that.*

*Also, at the same time, we needed an easy RGB888 to RGB565 converter because the TFT library uses 16-bit colors. So, this is the combo tool we created.*

*There's nothing really special in the commands, just follow the steps and you should be good to go. This is compilable in Windows and Linux using CMake.*
