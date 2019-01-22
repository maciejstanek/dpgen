Digital pattern generator
=========================

This is a digital pattern generator designed to run on boards with [`mraa`](https://github.com/intel-iot-devkit/mraa) library.

Installation
------------

Call the following commands to install the generator:
```bash
git clone https://github.com/maciejstanek/dpgen.git && cd dpgen
mkdir build && cd build
cmake ..
cmake --build . --target install
```

The generator is now accessible via `dpgen` command. Example pattern files are located in `/usr/share/dpgen`.

Usage
-----

Getting help:
```bash
dpgen -h
```

Generate a square wave on pin 13 with a frequency 30Hz:
```bash
dpgen -r -f 30 /usr/share/dpgen/square.dpd
```

Write a custom pattern (2b Gray code) and run it:
```bash
# Two signals will be used.
echo '2' > gray_2b.dpd
# First one on pin 7, second one on pin 8.
echo '7 8' >> gray_2b.dpd
# Set both signals to zero in time zero.
echo '0 0' >> gray_2b.dpd
# Set first signal to zero and second signal to one in time one.
echo '0 1' >> gray_2b.dpd
# &c.
echo '1 1' >> gray_2b.dpd
# &c.
echo '1 0' >> gray_2b.dpd
# Run the generator with a custom pattern.
dpgen -r -f 100 gray_2b.dpd
```
