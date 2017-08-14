# TS100_NG

[![build status](http://gitlab01.ncc-1701-d/marco/ts100_ng/badges/master/build.svg)](http://gitlab01.ncc-1701-d/marco/ts100_ng/commits/master)

Alternative firmware for TS100 soldering iron.

Forked from [Ralim/ts100](https://github.com/Ralim/ts100).

## Goals
* Better and stable control loop(mostly done)
* some sort of autotune/dynamic adjustment for varying input voltages
* clean and maintainable code style

## PWM implementation details
PWM frequency: 10 Hz  
Temperature measurement is done synchronus at the end of the PWM low phase.
Picture below:  
Iron is idle at setpoint temperature.(see statistics display in the picture)
![PWM Idle](doc/images/PWM_Idle.png)