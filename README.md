# sabvoton-controller
A controller for the sabvoton ebike esc.

## Pinout reference
```
---------------------------------------------------
| 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 10 |
---------------------------------------------------
| 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 |
---------------------------------------------------
| 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 |
---------------------------------------------------
```

 - 01: speed (0V - Battery voltage)
 - 02: programming (brown-blue)
 - 03: low speed (controlled by gnd)
 - 04: high speed (controlled by gnd)
 - 05: brake (controlled by gnd)
 - 06: service (unused)
 - 07: empty
 - 08: 5V
 - 09: 5V square hall sensor (speedometer)
 - 10: empty
 - 11: battery voltage
 - 12: programming (blue-yellow)
 - 13: programming (green-black)
 - 14: programming (red-black)
 - 15: brake (controlled by 12v)
 - 16: reverse (controlled by gnd)
 - 17: gnd
 - 18: gnd
 - 19: throttle (0V - 5V)?
 - 20: ignition (controlled by battery voltage)
 - 21: engine phase (anti-theft)
 - 22: empty
 - 23: regen (controlled by gnd)
 - 24: soft-start (connected to 26)
 - 25: cruise control (controlled by gnd)
 - 26: soft-start (connected to 24)
 - 27: gnd
 - 28: gnd
 - 29: alarm (controlled by gnd)
 - 30: service (unused)

## Working with the controller

### Connectors
 - 1: programming connector (same as the original)
 - 2: usb connector (for programming the arduino)
  
### Functions: 
 - 1: set current gear (low, mid, high) - pins 03, 04
 - 2: set motor power based on the torque sensor input - pin 19
 - 3: read battery voltage - pin 11
 - 4: turn controller on/off - pin 20
 - 5: enable/disable soft start - pins 24, 26
 - 6: get engine temperature - white wire
 - 7: get engine rpm - white wire
 - 8: get controller temperature - additional sensor
 - 9: get battery temperature - additional sensor
 - 10: send data to the display - additional display
 - 11: get data from the display - additional display
