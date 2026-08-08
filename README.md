# Medicine Dispenser

A reviewed and corrected version of this project, with a build check and
fuller documentation, is in [embedded-iot-projects / medicine-dispenser](https://github.com/Penchal9959/embedded-iot-projects/tree/main/medicine-dispenser) alongside the others from the same
series.

## What this was

A pill reminder with four daily alarms. At each scheduled time a buzzer sounds
and the LED above the right compartment lights, so the correct dose can be
found without reading a label. It was built for a diabetic relative who could
not.

The schedule is set with pushbuttons and held in EEPROM, so it survives a
power cut. A DS1307 keeps the time on a coin cell.

## Hardware

Arduino UNO, DS1307 real-time clock, pushbuttons, LEDs, buzzer.

## Licence

[MIT](LICENSE)
