#!/bin/bash
set -e
make clean
make
make flash || make flash
