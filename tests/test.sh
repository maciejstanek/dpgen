#!/bin/bash

>&2 ../src/dpgen -h

>&2 ../src/dpgen -f 2 -d ../examples/square.dpd

>&2 ../src/dpgen -f 10 -d ../examples/4bit.dpd

>&2 ../src/dpgen -f 2 -d missing_values.dpd
