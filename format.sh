#!/bin/bash
python tool/includeguardformatter.py src
find . -iname *.h -o -iname *.cpp | xargs clang-format -i
