#!/bin/bash

var1="first"
var2="second"
var3="third"

echo $var1
echo $var2
echo $var3

var4="$var1$var2$var3"

echo $var4

echo ${var4:11}

echo "${var4/third/forth}"




