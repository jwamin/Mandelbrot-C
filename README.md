# Mandelbrot-C

![Set](hi-res-zoom.jpg?raw=true "Screenshot")

### Drawing the set with the C Programming Language

`.ppm` output

current status - able to draw regions from the set by setting the max dimensions, origin, height and width. (pictured)

CMake configuration for build with macOS or WSL / Linux.

### Working on...

* Point and Rect Structs for easier function call sites 

* POSIX Threaded rendering of tiles for assembling into complete image

* Static library for use in Graphical Apps

* CLI

### Nice Ideas

More sophisticated image generation with `Cairo`

Better Colours, function or structure to substitute colors

Threading (VERY single threaded right now)

JPEG or PNG output

Hardware Acceleration? - Metal or OpenGL Fragment Shader

### Resources

[Rosetta Code](http://www.rosettacode.org/wiki/Bitmap/Write_a_PPM_file#C)

[Joni's Blog - The Mindful Programmer](https://jonisalonen.com/2013/lets-draw-the-mandelbrot-set/)

[Bitmap images without any external libraries](https://stackoverflow.com/questions/50090500/create-simple-bitmap-in-c-without-external-libraries)

[LibJpeg example](https://github.com/LuaDist/libjpeg/blob/master/example.c)