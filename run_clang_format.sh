#!/bin/bash

find . \( -name '*.cpp' -o -name '*.hpp' \) | xargs /usr/bin/clang-format-10 -i