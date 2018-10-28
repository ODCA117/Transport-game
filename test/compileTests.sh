#!/usr/bin/env bash
# if first time running test or if main has been modified run first
# g++ mainTest.cpp -c
g++ -std=c++11 mainTest.o NetworkTest.cpp -o tests
