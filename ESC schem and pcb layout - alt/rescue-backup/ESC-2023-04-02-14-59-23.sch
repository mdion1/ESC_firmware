EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ESC
LIBS:ESC-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L PIC16F18346 U1
U 1 1 5B00F91F
P 2200 5600
F 0 "U1" H 2200 6750 60  0000 C CNN
F 1 "PIC16F18346" H 2200 6650 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-20W_7.5x12.8mm_Pitch1.27mm" H 2950 5650 60  0001 C CNN
F 3 "" H 2950 5650 60  0001 C CNN
	1    2200 5600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5B00FB02
P 2800 6700
F 0 "#PWR01" H 2800 6450 50  0001 C CNN
F 1 "GND" H 2800 6550 50  0000 C CNN
F 2 "" H 2800 6700 50  0001 C CNN
F 3 "" H 2800 6700 50  0001 C CNN
	1    2800 6700
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR02
U 1 1 5B00FB1E
P 3850 6300
F 0 "#PWR02" H 3850 6150 50  0001 C CNN
F 1 "+3.3V" H 3850 6440 50  0000 C CNN
F 2 "" H 3850 6300 50  0001 C CNN
F 3 "" H 3850 6300 50  0001 C CNN
	1    3850 6300
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5B00FEAD
P 3150 6450
F 0 "C4" H 3175 6550 50  0000 L CNN
F 1 "100n" H 3175 6350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 3188 6300 50  0001 C CNN
F 3 "" H 3150 6450 50  0001 C CNN
	1    3150 6450
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x03 J3
U 1 1 5B00FF55
P 9100 4850
F 0 "J3" H 9100 5050 50  0000 C CNN
F 1 "Conn_01x03" H 9100 4650 50  0000 C CNN
F 2 "ESC_footprints:Wire-to-board_1x3" H 9100 4850 50  0001 C CNN
F 3 "" H 9100 4850 50  0001 C CNN
	1    9100 4850
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J2
U 1 1 5B00FFBA
P 9100 4300
F 0 "J2" H 9100 4400 50  0000 C CNN
F 1 "Conn_01x02" H 9100 4100 50  0000 C CNN
F 2 "ESC_footprints:Wire-to-board_1x2" H 9100 4300 50  0001 C CNN
F 3 "" H 9100 4300 50  0001 C CNN
	1    9100 4300
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 5B0103A9
P 4250 4450
F 0 "C6" H 4275 4550 50  0000 L CNN
F 1 "1.3n" H 4275 4350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 4288 4300 50  0001 C CNN
F 3 "" H 4250 4450 50  0001 C CNN
	1    4250 4450
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 5B0103FC
P 5700 5900
F 0 "R11" V 5780 5900 50  0000 C CNN
F 1 "1k3" V 5700 5900 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5630 5900 50  0001 C CNN
F 3 "" H 5700 5900 50  0001 C CNN
	1    5700 5900
	-1   0    0    1   
$EndComp
$Comp
L R R9
U 1 1 5B010445
P 5350 5450
F 0 "R9" V 5430 5450 50  0000 C CNN
F 1 "1k3" V 5350 5450 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5280 5450 50  0001 C CNN
F 3 "" H 5350 5450 50  0001 C CNN
	1    5350 5450
	-1   0    0    1   
$EndComp
$Comp
L R R6
U 1 1 5B01049A
P 4850 5000
F 0 "R6" V 4930 5000 50  0000 C CNN
F 1 "1k3" V 4850 5000 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4780 5000 50  0001 C CNN
F 3 "" H 4850 5000 50  0001 C CNN
	1    4850 5000
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x04 J4
U 1 1 5B0112F1
P 9100 5450
F 0 "J4" H 9100 5650 50  0000 C CNN
F 1 "Conn_01x04" H 9100 5150 50  0000 C CNN
F 2 "ESC_footprints:Wire_to_board_cluster__4" H 9100 5450 50  0001 C CNN
F 3 "" H 9100 5450 50  0001 C CNN
	1    9100 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 6300 3850 6300
Connection ~ 3150 6300
Wire Wire Line
	2800 6600 3450 6600
Wire Wire Line
	2800 6500 2800 6700
Connection ~ 2800 6600
$Comp
L GND #PWR03
U 1 1 5B0193B6
P 4250 4650
F 0 "#PWR03" H 4250 4400 50  0001 C CNN
F 1 "GND" H 4250 4500 50  0000 C CNN
F 2 "" H 4250 4650 50  0001 C CNN
F 3 "" H 4250 4650 50  0001 C CNN
	1    4250 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 4650 4250 4600
$Comp
L R R8
U 1 1 5B01964F
P 5000 4450
F 0 "R8" V 5080 4450 50  0000 C CNN
F 1 "10k" V 5000 4450 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4930 4450 50  0001 C CNN
F 3 "" H 5000 4450 50  0001 C CNN
	1    5000 4450
	-1   0    0    1   
$EndComp
$Comp
L R R10
U 1 1 5B0196A2
P 5450 4750
F 0 "R10" V 5530 4750 50  0000 C CNN
F 1 "10k" V 5450 4750 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5380 4750 50  0001 C CNN
F 3 "" H 5450 4750 50  0001 C CNN
	1    5450 4750
	-1   0    0    1   
$EndComp
$Comp
L R R12
U 1 1 5B0196F2
P 5800 5050
F 0 "R12" V 5880 5050 50  0000 C CNN
F 1 "10k" V 5800 5050 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5730 5050 50  0001 C CNN
F 3 "" H 5800 5050 50  0001 C CNN
	1    5800 5050
	-1   0    0    1   
$EndComp
Wire Wire Line
	3650 4700 2800 4700
$Comp
L C C10
U 1 1 5B01AC1C
P 5900 5900
F 0 "C10" H 5925 6000 50  0000 L CNN
F 1 "1.3n" H 5925 5800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5938 5750 50  0001 C CNN
F 3 "" H 5900 5900 50  0001 C CNN
	1    5900 5900
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 5B01AC94
P 5100 5000
F 0 "C8" H 5125 5100 50  0000 L CNN
F 1 "1.3n" H 5125 4900 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5138 4850 50  0001 C CNN
F 3 "" H 5100 5000 50  0001 C CNN
	1    5100 5000
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 5B01AD63
P 5550 5450
F 0 "C9" H 5575 5550 50  0000 L CNN
F 1 "1.3n" H 5575 5350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5588 5300 50  0001 C CNN
F 3 "" H 5550 5450 50  0001 C CNN
	1    5550 5450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5B01C081
P 5900 6150
F 0 "#PWR04" H 5900 5900 50  0001 C CNN
F 1 "GND" H 5900 6000 50  0000 C CNN
F 2 "" H 5900 6150 50  0001 C CNN
F 3 "" H 5900 6150 50  0001 C CNN
	1    5900 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 6050 5900 6150
Wire Wire Line
	4850 6100 5900 6100
Wire Wire Line
	5550 6100 5550 5600
Connection ~ 5900 6100
Wire Wire Line
	5100 6100 5100 5150
Connection ~ 5550 6100
Wire Wire Line
	5700 6050 5700 6100
Connection ~ 5700 6100
Wire Wire Line
	5350 5600 5350 6100
Connection ~ 5350 6100
Wire Wire Line
	4850 5150 4850 6100
Connection ~ 5100 6100
Wire Wire Line
	4400 4850 5100 4850
Wire Wire Line
	5000 4600 5000 4850
Connection ~ 5000 4850
Wire Wire Line
	4250 5300 5550 5300
Wire Wire Line
	5450 4900 5450 5300
Connection ~ 5450 5300
Wire Wire Line
	4000 5750 5900 5750
Wire Wire Line
	5800 5200 5800 5750
Connection ~ 5800 5750
Wire Wire Line
	5800 4900 6300 4900
Wire Wire Line
	5450 4600 6300 4600
Wire Wire Line
	5000 4300 6300 4300
Wire Wire Line
	4000 5750 4000 5300
Wire Wire Line
	4000 5300 2800 5300
Connection ~ 5700 5750
Wire Wire Line
	4250 5300 4250 5100
Wire Wire Line
	4250 5100 2800 5100
Connection ~ 5350 5300
Wire Wire Line
	2800 4900 4400 4900
Wire Wire Line
	4400 4900 4400 4850
Connection ~ 4850 4850
$Comp
L R R5
U 1 1 5B01E791
P 4500 4450
F 0 "R5" V 4580 4450 50  0000 C CNN
F 1 "1k3" V 4500 4450 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4430 4450 50  0001 C CNN
F 3 "" H 4500 4450 50  0001 C CNN
	1    4500 4450
	-1   0    0    1   
$EndComp
$Comp
L R R4
U 1 1 5B01E824
P 4500 3700
F 0 "R4" V 4580 3700 50  0000 C CNN
F 1 "10k" V 4500 3700 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4430 3700 50  0001 C CNN
F 3 "" H 4500 3700 50  0001 C CNN
	1    4500 3700
	-1   0    0    1   
$EndComp
Wire Wire Line
	4250 4600 4500 4600
Wire Wire Line
	3650 4050 3650 4700
$Comp
L +BATT #PWR05
U 1 1 5B01EAE9
P 4500 3450
F 0 "#PWR05" H 4500 3300 50  0001 C CNN
F 1 "+BATT" H 4500 3590 50  0000 C CNN
F 2 "" H 4500 3450 50  0001 C CNN
F 3 "" H 4500 3450 50  0001 C CNN
	1    4500 3450
	1    0    0    -1  
$EndComp
$Comp
L POT P1
U 1 1 5B01EC14
P 4500 4050
F 0 "P1" V 4325 4050 50  0000 C CNN
F 1 "1k" V 4400 4050 50  0000 C CNN
F 2 "ESC_footprints:Potentiometer_Trimmer_Bourns_3223W" H 4500 4050 50  0001 C CNN
F 3 "" H 4500 4050 50  0001 C CNN
	1    4500 4050
	-1   0    0    1   
$EndComp
Wire Wire Line
	4500 3450 4500 3550
Wire Wire Line
	4500 4200 4500 4300
Wire Wire Line
	4350 4050 4350 3900
Wire Wire Line
	4350 3900 4500 3900
Wire Wire Line
	4500 3900 4500 3850
Wire Wire Line
	2800 5900 3250 5900
Wire Wire Line
	1600 6100 1000 6100
Wire Wire Line
	1600 6500 1000 6500
Text Label 3250 5900 0    60   ~ 0
~SS
Text Label 1000 6100 0    60   ~ 0
MOSI
Text Label 1000 6500 0    60   ~ 0
SCK
Wire Wire Line
	1600 4700 1000 4700
Wire Wire Line
	1600 4900 1000 4900
Wire Wire Line
	1600 5300 1000 5300
Text Label 1000 4700 0    60   ~ 0
ICSP_data
Text Label 1000 4900 0    60   ~ 0
ICSP_clk
Text Label 1000 5300 0    60   ~ 0
~MCLR
Wire Wire Line
	1600 5500 1000 5500
Wire Wire Line
	1600 5700 1000 5700
Wire Wire Line
	1600 5900 1000 5900
Wire Wire Line
	1600 6300 1000 6300
Wire Wire Line
	2800 6100 3250 6100
Wire Wire Line
	2800 5700 3250 5700
Wire Wire Line
	1650 3350 1150 3350
Wire Wire Line
	1650 3450 850  3450
Wire Wire Line
	1650 3550 850  3550
Wire Wire Line
	1650 3650 1150 3650
Wire Wire Line
	1650 3750 1150 3750
Text Label 1150 3350 0    60   ~ 0
~MCLR
$Comp
L +3.3V #PWR06
U 1 1 5B02A008
P 850 3450
F 0 "#PWR06" H 850 3300 50  0001 C CNN
F 1 "+3.3V" H 850 3590 50  0000 C CNN
F 2 "" H 850 3450 50  0001 C CNN
F 3 "" H 850 3450 50  0001 C CNN
	1    850  3450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5B02A3AF
P 850 3550
F 0 "#PWR07" H 850 3300 50  0001 C CNN
F 1 "GND" H 850 3400 50  0000 C CNN
F 2 "" H 850 3550 50  0001 C CNN
F 3 "" H 850 3550 50  0001 C CNN
	1    850  3550
	1    0    0    -1  
$EndComp
Text Label 1150 3650 0    60   ~ 0
ICSP_data
Text Label 1150 3750 0    60   ~ 0
ICSP_clk
$Comp
L C C1
U 1 1 5B02CFBE
P 1300 1550
F 0 "C1" H 1325 1650 50  0000 L CNN
F 1 "10n" H 1325 1450 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1338 1400 50  0001 C CNN
F 3 "" H 1300 1550 50  0001 C CNN
	1    1300 1550
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5B02D051
P 1300 1850
F 0 "R1" V 1380 1850 50  0000 C CNN
F 1 "1" V 1300 1850 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1230 1850 50  0001 C CNN
F 3 "" H 1300 1850 50  0001 C CNN
	1    1300 1850
	-1   0    0    1   
$EndComp
Text Notes 900  1150 0    79   ~ 16
Snubber circuitry
$Comp
L C C2
U 1 1 5B02E2B5
P 1300 2250
F 0 "C2" H 1325 2350 50  0000 L CNN
F 1 "10n" H 1325 2150 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1338 2100 50  0001 C CNN
F 3 "" H 1300 2250 50  0001 C CNN
	1    1300 2250
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5B02E2BB
P 1300 2550
F 0 "R2" V 1380 2550 50  0000 C CNN
F 1 "1" V 1300 2550 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1230 2550 50  0001 C CNN
F 3 "" H 1300 2550 50  0001 C CNN
	1    1300 2550
	-1   0    0    1   
$EndComp
$Comp
L C C3
U 1 1 5B02E3EF
P 2050 1800
F 0 "C3" H 2075 1900 50  0000 L CNN
F 1 "10n" H 2075 1700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2088 1650 50  0001 C CNN
F 3 "" H 2050 1800 50  0001 C CNN
	1    2050 1800
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5B02E3F5
P 2050 2100
F 0 "R3" V 2130 2100 50  0000 C CNN
F 1 "1" V 2050 2100 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1980 2100 50  0001 C CNN
F 3 "" H 2050 2100 50  0001 C CNN
	1    2050 2100
	-1   0    0    1   
$EndComp
Wire Wire Line
	1300 2000 1300 2100
Wire Wire Line
	850  1400 2050 1400
Wire Wire Line
	850  2700 2050 2700
Wire Wire Line
	1300 2050 850  2050
Connection ~ 1300 2050
Wire Wire Line
	2050 1400 2050 1650
Connection ~ 1300 1400
Wire Wire Line
	2050 2700 2050 2250
Connection ~ 1300 2700
$Comp
L C C5
U 1 1 5B02F531
P 3450 6450
F 0 "C5" H 3475 6550 50  0000 L CNN
F 1 "10u" H 3475 6350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 3488 6300 50  0001 C CNN
F 3 "" H 3450 6450 50  0001 C CNN
	1    3450 6450
	1    0    0    -1  
$EndComp
Connection ~ 3150 6600
Wire Wire Line
	3650 4050 4350 4050
Connection ~ 4250 4050
Wire Wire Line
	4250 4050 4250 4300
Text Notes 900  3100 0    79   ~ 16
In Circuit Programming
Text Notes 1600 4350 0    79   ~ 16
Microcontroller
Wire Wire Line
	8050 4750 8900 4750
Wire Wire Line
	7950 4850 8900 4850
Wire Wire Line
	7850 4950 8900 4950
$Comp
L +BATT #PWR08
U 1 1 5B03FD7F
P 8650 4300
F 0 "#PWR08" H 8650 4150 50  0001 C CNN
F 1 "+BATT" H 8650 4440 50  0000 C CNN
F 2 "" H 8650 4300 50  0001 C CNN
F 3 "" H 8650 4300 50  0001 C CNN
	1    8650 4300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 5B03FDF3
P 8650 4400
F 0 "#PWR09" H 8650 4150 50  0001 C CNN
F 1 "GND" H 8650 4250 50  0000 C CNN
F 2 "" H 8650 4400 50  0001 C CNN
F 3 "" H 8650 4400 50  0001 C CNN
	1    8650 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 4300 8900 4300
Wire Wire Line
	8900 4400 8650 4400
Text Label 8450 5450 0    60   ~ 0
MOSI
Text Label 8450 5550 0    60   ~ 0
SCK
Text Label 8450 5650 0    60   ~ 0
~SS
$Comp
L +3.3V #PWR010
U 1 1 5B040F5F
P 8450 5350
F 0 "#PWR010" H 8450 5200 50  0001 C CNN
F 1 "+3.3V" H 8450 5490 50  0000 C CNN
F 2 "" H 8450 5350 50  0001 C CNN
F 3 "" H 8450 5350 50  0001 C CNN
	1    8450 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 5350 8900 5350
Wire Wire Line
	8900 5450 8450 5450
Wire Wire Line
	8450 5550 8900 5550
Wire Wire Line
	8900 5650 8450 5650
Text Notes 8250 3900 0    79   ~ 16
Header pins
$Sheet
S 9000 2750 1600 850 
U 5B0419C7
F0 "Motor Drivers" 60
F1 "file5B0419C6.sch" 60
F2 "Mtr_A" I L 9000 2850 60 
F3 "Mtr_B" I L 9000 3000 60 
F4 "Mtr_C" I L 9000 3150 60 
F5 "A_hi/lo" I L 9000 3300 60 
F6 "A_on/off" I L 9000 3450 60 
F7 "C_hi/lo" I R 10600 3500 60 
F8 "C_on/off" I R 10600 3350 60 
F9 "B_hi/lo" I R 10600 3000 60 
F10 "B_on/off" I R 10600 3150 60 
$EndSheet
Text Label 1000 5500 0    60   ~ 0
A_hi/lo
Text Label 1000 5700 0    60   ~ 0
A_on/off
Text Label 1000 5900 0    60   ~ 0
B_hi/lo
Text Label 1000 6300 0    60   ~ 0
B_on/off
Text Label 8250 3450 0    60   ~ 0
A_on/off
Text Label 8250 3300 0    60   ~ 0
A_hi/lo
Wire Wire Line
	8250 3300 9000 3300
Wire Wire Line
	9000 3450 8250 3450
Wire Wire Line
	8050 4750 8050 2850
Wire Wire Line
	8050 2850 9000 2850
Wire Wire Line
	7950 4850 7950 3000
Wire Wire Line
	7950 3000 9000 3000
Wire Wire Line
	7850 4950 7850 3150
Wire Wire Line
	7850 3150 9000 3150
Text Label 6300 4900 0    60   ~ 0
Mtr_C
Text Label 6300 4300 0    60   ~ 0
Mtr_A
Text Label 6300 4600 0    60   ~ 0
Mtr_B
Text Label 8400 4750 0    60   ~ 0
Mtr_A
Text Label 8400 4850 0    60   ~ 0
Mtr_B
Text Label 8400 4950 0    60   ~ 0
Mtr_C
Text Label 3250 5700 0    60   ~ 0
C_hi/lo
Text Label 3250 6100 0    60   ~ 0
C_on/off
Wire Wire Line
	10600 3000 10700 3000
Wire Wire Line
	10600 3150 10700 3150
Wire Wire Line
	10600 3350 10700 3350
Wire Wire Line
	10600 3500 10700 3500
Text Label 10700 3000 0    60   ~ 0
B_hi/lo
Text Label 10700 3150 0    60   ~ 0
B_on/off
Text Label 10700 3350 0    60   ~ 0
C_on/off
Text Label 10700 3500 0    60   ~ 0
C_hi/lo
Connection ~ 3450 6300
Text Label 850  1400 0    60   ~ 0
Mtr_A
Text Label 850  2050 0    60   ~ 0
Mtr_B
Text Label 850  2700 0    60   ~ 0
Mtr_C
$Comp
L Conn_01x05 J1
U 1 1 5B0A2FCA
P 1850 3550
F 0 "J1" H 1850 3850 50  0000 C CNN
F 1 "Conn_01x05" H 1850 3250 50  0000 C CNN
F 2 "ESC_footprints:Male_header_pins_1x5" H 1850 3550 50  0001 C CNN
F 3 "" H 1850 3550 50  0001 C CNN
	1    1850 3550
	1    0    0    -1  
$EndComp
$Comp
L C C12
U 1 1 5B0B351A
P 5000 3600
F 0 "C12" H 5025 3700 50  0000 L CNN
F 1 "100n" H 5025 3500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5038 3450 50  0001 C CNN
F 3 "" H 5000 3600 50  0001 C CNN
	1    5000 3600
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 5B0B3705
P 5300 3600
F 0 "C13" H 5325 3700 50  0000 L CNN
F 1 "10u" H 5325 3500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5338 3450 50  0001 C CNN
F 3 "" H 5300 3600 50  0001 C CNN
	1    5300 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 3450 5300 3450
Connection ~ 5000 3450
Wire Wire Line
	5000 3750 5300 3750
$Comp
L GND #PWR011
U 1 1 5B0B3B36
P 5300 3750
F 0 "#PWR011" H 5300 3500 50  0001 C CNN
F 1 "GND" H 5300 3600 50  0000 C CNN
F 2 "" H 5300 3750 50  0001 C CNN
F 3 "" H 5300 3750 50  0001 C CNN
	1    5300 3750
	1    0    0    -1  
$EndComp
$EndSCHEMATC
