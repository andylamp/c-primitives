#!/bin/bash

DEBUG_FLAG="DEBUG";

# compile while cleaning up
if [[ "$1" == $(DEBUG_FLAG) ]]; then
   clear; make clean && make all
else
   clear; make clean && make DEBUG=1 all
fi
