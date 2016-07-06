# WinApiWrappers

#Description
Wrappers for Win Api written in C++ and they work for Cygwin ( haven't tested them for MingW yet.)

#Instructions
For using them place the `.a` file in the directory of your source c++ code and use the following command to compile : 
$gcc test.cpp -L. -lfile

or if you have placed it in another directory replace L<directory> with L.

#Please Note : I recommend you to use the static library becuase this library is very lightweight and it won't alter the size of the executable much

Currently I have worked on wrapping File Mangement functions and it will be thanked if you helped and cooperated with me on Registery Management one.

Hope it helps in your projects :)

Cheers, Ehsan
