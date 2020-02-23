#!/bin/bash

find . -name *.cpp -o -name *.h | xargs nkf -Lu -w --overwrite
python tool/includeguardformatter.py src
find . -iname *.h -o -iname *.cpp | xargs clang-format -i
