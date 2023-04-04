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
LIBS:stm32Morpho
LIBS:sn65hvd1050
LIBS:mechanical
LIBS:STM32F303-RIR4-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L CN7 J0
U 1 1 642AE579
P 3725 2150
F 0 "J0" H 3775 3150 50  0000 C CNN
F 1 "CN7" H 3775 1150 50  0000 C CNN
F 2 "stm32Morpho:ST_MorfoHeader" H 3725 2150 50  0001 C CNN
F 3 "" H 3725 2150 50  0001 C CNN
	1    3725 2150
	1    0    0    -1  
$EndComp
$Comp
L CN10 J1
U 1 1 642AE5A8
P 6225 2200
F 0 "J1" H 6275 3200 50  0000 C CNN
F 1 "CN10" H 6275 1200 50  0000 C CNN
F 2 "stm32Morpho:ST_MorfoHeader" H 6225 2200 50  0001 C CNN
F 3 "" H 6225 2200 50  0001 C CNN
	1    6225 2200
	1    0    0    -1  
$EndComp
$Comp
L RJ45 J101
U 1 1 642B21CC
P 9325 4250
F 0 "J101" H 9525 4750 50  0000 C CNN
F 1 "LCC" H 9175 4750 50  0000 C CNN
F 2 "Connectors:RJ45_8" H 9325 4250 50  0001 C CNN
F 3 "" H 9325 4250 50  0001 C CNN
	1    9325 4250
	0    1    1    0   
$EndComp
$Comp
L RJ45 J102
U 1 1 642B2213
P 9375 5950
F 0 "J102" H 9575 6450 50  0000 C CNN
F 1 "LCC" H 9225 6450 50  0000 C CNN
F 2 "Connectors:RJ45_8" H 9375 5950 50  0001 C CNN
F 3 "" H 9375 5950 50  0001 C CNN
	1    9375 5950
	0    1    1    0   
$EndComp
NoConn ~ 9675 4800
NoConn ~ 9725 6500
Wire Wire Line
	8725 5600 8925 5600
Wire Wire Line
	8725 3900 8725 5600
Wire Wire Line
	8725 3900 8875 3900
Wire Wire Line
	8875 4000 8675 4000
Wire Wire Line
	8675 4000 8675 5700
Wire Wire Line
	8675 5700 8925 5700
Wire Wire Line
	8925 5800 8625 5800
Wire Wire Line
	8625 4100 8625 6350
Wire Wire Line
	8625 4100 8875 4100
Wire Wire Line
	8875 4200 8575 4200
Wire Wire Line
	8575 4200 8575 5900
Wire Wire Line
	8575 5900 8925 5900
Wire Wire Line
	8925 6000 8550 6000
Wire Wire Line
	8550 6000 8550 4300
Wire Wire Line
	8550 4300 8875 4300
Wire Wire Line
	8875 4400 8500 4400
Wire Wire Line
	8500 4400 8500 6100
Wire Wire Line
	8500 6100 8925 6100
Wire Wire Line
	8450 6200 8925 6200
Wire Wire Line
	8450 6200 8450 4500
Wire Wire Line
	8450 4500 8875 4500
Wire Wire Line
	8875 4600 8400 4600
Wire Wire Line
	8400 4600 8400 6300
Wire Wire Line
	8400 6300 8925 6300
$Comp
L SN65HVD1050 U101
U 1 1 642B29F1
P 7650 5125
F 0 "U101" H 7550 5525 50  0000 R CNN
F 1 "SN65HVD1050" H 7550 5425 50  0000 R CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 7650 4625 50  0001 C CNN
F 3 "" H 7550 5525 50  0001 C CNN
	1    7650 5125
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 5125 8725 5125
Connection ~ 8725 5125
Wire Wire Line
	8050 5225 8675 5225
Connection ~ 8675 5225
$Comp
L +5V #PWR01
U 1 1 642B2BCC
P 7650 4750
F 0 "#PWR01" H 7650 4600 50  0001 C CNN
F 1 "+5V" H 7650 4890 50  0000 C CNN
F 2 "" H 7650 4750 50  0001 C CNN
F 3 "" H 7650 4750 50  0001 C CNN
	1    7650 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 4750 7650 4825
NoConn ~ 7250 5225
$Comp
L GND #PWR02
U 1 1 642B2C2F
P 7650 5625
F 0 "#PWR02" H 7650 5375 50  0001 C CNN
F 1 "GND" H 7650 5475 50  0000 C CNN
F 2 "" H 7650 5625 50  0001 C CNN
F 3 "" H 7650 5625 50  0001 C CNN
	1    7650 5625
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 5525 7650 5625
Wire Wire Line
	7250 5325 7250 5525
Wire Wire Line
	7250 5525 7650 5525
$Comp
L C_Small C101
U 1 1 642B2D14
P 8125 4775
F 0 "C101" H 8135 4845 50  0000 L CNN
F 1 ".1 uf" H 8135 4695 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 8125 4775 50  0001 C CNN
F 3 "" H 8125 4775 50  0001 C CNN
	1    8125 4775
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR03
U 1 1 642B2D5D
P 8125 4625
F 0 "#PWR03" H 8125 4475 50  0001 C CNN
F 1 "+5V" H 8125 4765 50  0000 C CNN
F 2 "" H 8125 4625 50  0001 C CNN
F 3 "" H 8125 4625 50  0001 C CNN
	1    8125 4625
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 642B2DC6
P 8125 4925
F 0 "#PWR04" H 8125 4675 50  0001 C CNN
F 1 "GND" H 8125 4775 50  0000 C CNN
F 2 "" H 8125 4925 50  0001 C CNN
F 3 "" H 8125 4925 50  0001 C CNN
	1    8125 4925
	1    0    0    -1  
$EndComp
Wire Wire Line
	8125 4875 8125 4925
Wire Wire Line
	8125 4625 8125 4675
Text Label 6725 1800 0    60   ~ 0
CAN_TX
Text Label 6725 1900 0    60   ~ 0
CAN_RX
Text Label 7250 5125 2    60   ~ 0
CAN_RX
Text Label 7250 5025 2    60   ~ 0
CAN_TX
NoConn ~ 6725 1300
NoConn ~ 6725 1400
NoConn ~ 6725 1500
NoConn ~ 6725 1700
NoConn ~ 6725 2100
NoConn ~ 6725 2300
NoConn ~ 6725 2400
NoConn ~ 6725 2500
NoConn ~ 6725 2600
NoConn ~ 6725 2700
NoConn ~ 6725 2900
NoConn ~ 6725 3000
NoConn ~ 6725 3100
NoConn ~ 5825 3100
NoConn ~ 5825 3000
NoConn ~ 5825 2900
NoConn ~ 5825 2800
NoConn ~ 5825 2700
NoConn ~ 5825 2600
NoConn ~ 5825 2500
NoConn ~ 5825 2400
NoConn ~ 5825 2300
NoConn ~ 5825 2200
NoConn ~ 5825 2100
NoConn ~ 5825 2000
NoConn ~ 5825 1900
NoConn ~ 5825 1800
NoConn ~ 5825 1500
NoConn ~ 5825 1400
NoConn ~ 5825 1300
$Comp
L GND #PWR05
U 1 1 642B31FD
P 6825 2200
F 0 "#PWR05" H 6825 1950 50  0001 C CNN
F 1 "GND" H 6825 2050 50  0000 C CNN
F 2 "" H 6825 2200 50  0001 C CNN
F 3 "" H 6825 2200 50  0001 C CNN
	1    6825 2200
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR06
U 1 1 642B3253
P 5750 1600
F 0 "#PWR06" H 5750 1350 50  0001 C CNN
F 1 "GND" H 5750 1450 50  0000 C CNN
F 2 "" H 5750 1600 50  0001 C CNN
F 3 "" H 5750 1600 50  0001 C CNN
	1    5750 1600
	0    1    1    0   
$EndComp
$Comp
L GND #PWR07
U 1 1 642B3285
P 5750 1700
F 0 "#PWR07" H 5750 1450 50  0001 C CNN
F 1 "GND" H 5750 1550 50  0000 C CNN
F 2 "" H 5750 1700 50  0001 C CNN
F 3 "" H 5750 1700 50  0001 C CNN
	1    5750 1700
	0    1    1    0   
$EndComp
Wire Wire Line
	6825 2200 6725 2200
Wire Wire Line
	5750 1600 5825 1600
Wire Wire Line
	5750 1700 5825 1700
$Comp
L GND #PWR08
U 1 1 642B3393
P 6800 2800
F 0 "#PWR08" H 6800 2550 50  0001 C CNN
F 1 "GND" H 6800 2650 50  0000 C CNN
F 2 "" H 6800 2800 50  0001 C CNN
F 3 "" H 6800 2800 50  0001 C CNN
	1    6800 2800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6800 2800 6725 2800
NoConn ~ 6725 2000
NoConn ~ 6725 1600
Text Label 4225 2350 0    60   ~ 0
LCC_CAN_12V
Text Label 8400 6300 2    60   ~ 0
LCC_CAN_12V
NoConn ~ 4225 1250
NoConn ~ 4225 1350
NoConn ~ 4225 1450
NoConn ~ 4225 1650
NoConn ~ 4225 1850
NoConn ~ 4225 1950
$Comp
L +5V #PWR09
U 1 1 642B3761
P 4300 2050
F 0 "#PWR09" H 4300 1900 50  0001 C CNN
F 1 "+5V" H 4300 2190 50  0000 C CNN
F 2 "" H 4300 2050 50  0001 C CNN
F 3 "" H 4300 2050 50  0001 C CNN
	1    4300 2050
	0    1    1    0   
$EndComp
$Comp
L GND #PWR010
U 1 1 642B3793
P 4300 1550
F 0 "#PWR010" H 4300 1300 50  0001 C CNN
F 1 "GND" H 4300 1400 50  0000 C CNN
F 2 "" H 4300 1550 50  0001 C CNN
F 3 "" H 4300 1550 50  0001 C CNN
	1    4300 1550
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR011
U 1 1 642B37E9
P 4300 2150
F 0 "#PWR011" H 4300 1900 50  0001 C CNN
F 1 "GND" H 4300 2000 50  0000 C CNN
F 2 "" H 4300 2150 50  0001 C CNN
F 3 "" H 4300 2150 50  0001 C CNN
	1    4300 2150
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR012
U 1 1 642B383F
P 4300 2250
F 0 "#PWR012" H 4300 2000 50  0001 C CNN
F 1 "GND" H 4300 2100 50  0000 C CNN
F 2 "" H 4300 2250 50  0001 C CNN
F 3 "" H 4300 2250 50  0001 C CNN
	1    4300 2250
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR013
U 1 1 642B38A7
P 3250 2150
F 0 "#PWR013" H 3250 1900 50  0001 C CNN
F 1 "GND" H 3250 2000 50  0000 C CNN
F 2 "" H 3250 2150 50  0001 C CNN
F 3 "" H 3250 2150 50  0001 C CNN
	1    3250 2150
	0    1    1    0   
$EndComp
Wire Wire Line
	4300 1550 4225 1550
Wire Wire Line
	4300 2050 4225 2050
Wire Wire Line
	4300 2150 4225 2150
Wire Wire Line
	4300 2250 4225 2250
NoConn ~ 3325 1250
NoConn ~ 3325 1350
NoConn ~ 3325 1450
NoConn ~ 3325 1550
NoConn ~ 3325 1650
NoConn ~ 3325 1750
NoConn ~ 3325 1850
NoConn ~ 3325 1950
NoConn ~ 3325 2050
NoConn ~ 3325 2250
NoConn ~ 3325 2350
Wire Wire Line
	3325 2150 3250 2150
NoConn ~ 3325 2450
NoConn ~ 3325 2550
NoConn ~ 3325 2650
NoConn ~ 3325 2750
NoConn ~ 3325 2850
NoConn ~ 3325 2950
NoConn ~ 3325 3050
NoConn ~ 4225 3050
NoConn ~ 4225 2950
NoConn ~ 4225 2850
NoConn ~ 4225 2750
NoConn ~ 4225 2650
NoConn ~ 4225 2550
NoConn ~ 4225 2450
NoConn ~ 4225 1750
NoConn ~ 3525 2600
Connection ~ 8625 6100
Connection ~ 8625 5800
Connection ~ 8625 6200
$Comp
L GND #PWR014
U 1 1 642B3DF5
P 8625 6350
F 0 "#PWR014" H 8625 6100 50  0001 C CNN
F 1 "GND" H 8625 6200 50  0000 C CNN
F 2 "" H 8625 6350 50  0001 C CNN
F 3 "" H 8625 6350 50  0001 C CNN
	1    8625 6350
	1    0    0    -1  
$EndComp
$Comp
L Mounting_Hole MK101
U 1 1 642B400B
P 3200 4375
F 0 "MK101" H 3200 4575 50  0000 C CNN
F 1 "Mounting_Hole" H 3200 4500 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3" H 3200 4375 50  0001 C CNN
F 3 "" H 3200 4375 50  0001 C CNN
	1    3200 4375
	1    0    0    -1  
$EndComp
$Comp
L Mounting_Hole MK102
U 1 1 642B4089
P 3550 4375
F 0 "MK102" H 3550 4575 50  0000 C CNN
F 1 "Mounting_Hole" H 3550 4500 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3" H 3550 4375 50  0001 C CNN
F 3 "" H 3550 4375 50  0001 C CNN
	1    3550 4375
	1    0    0    -1  
$EndComp
$Comp
L Mounting_Hole MK103
U 1 1 642B40C9
P 3925 4375
F 0 "MK103" H 3925 4575 50  0000 C CNN
F 1 "Mounting_Hole" H 3925 4500 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3" H 3925 4375 50  0001 C CNN
F 3 "" H 3925 4375 50  0001 C CNN
	1    3925 4375
	1    0    0    -1  
$EndComp
$Comp
L Mounting_Hole MK104
U 1 1 642B40FE
P 4350 4375
F 0 "MK104" H 4350 4575 50  0000 C CNN
F 1 "Mounting_Hole" H 4350 4500 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3" H 4350 4375 50  0001 C CNN
F 3 "" H 4350 4375 50  0001 C CNN
	1    4350 4375
	1    0    0    -1  
$EndComp
$Comp
L LM358 U102
U 1 1 642C3F7A
P 7600 3100
F 0 "U102" H 7600 3300 50  0000 L CNN
F 1 "LM358" H 7600 2900 50  0000 L CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 7600 3100 50  0001 C CNN
F 3 "" H 7600 3100 50  0001 C CNN
F 4 "595-LM358DR" H 7600 3100 60  0001 C CNN "Mouser Part Number"
	1    7600 3100
	1    0    0    1   
$EndComp
$Comp
L LM358 U102
U 2 1 642C4128
P 7625 4025
F 0 "U102" H 7625 4225 50  0000 L CNN
F 1 "LM358" H 7625 3825 50  0000 L CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 7625 4025 50  0001 C CNN
F 3 "" H 7625 4025 50  0001 C CNN
F 4 "595-LM358DR" H 7625 4025 60  0001 C CNN "Mouser Part Number"
	2    7625 4025
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 3000 7300 2625
Wire Wire Line
	7300 2625 8050 2625
Wire Wire Line
	8050 2625 8050 3100
Wire Wire Line
	7900 3100 8150 3100
Wire Wire Line
	7325 4125 7325 4575
Wire Wire Line
	7325 4575 8025 4575
Wire Wire Line
	8025 4575 8025 4025
Wire Wire Line
	7925 4025 8125 4025
Text Label 7325 3925 2    60   ~ 0
CAN_RX
Text Label 7300 3200 2    60   ~ 0
CAN_TX
$Comp
L +5V #PWR015
U 1 1 642C4BAF
P 7525 3675
F 0 "#PWR015" H 7525 3525 50  0001 C CNN
F 1 "+5V" H 7525 3815 50  0000 C CNN
F 2 "" H 7525 3675 50  0001 C CNN
F 3 "" H 7525 3675 50  0001 C CNN
	1    7525 3675
	1    0    0    -1  
$EndComp
Wire Wire Line
	7525 3675 7525 3725
$Comp
L GND #PWR016
U 1 1 642C4C57
P 7525 4375
F 0 "#PWR016" H 7525 4125 50  0001 C CNN
F 1 "GND" H 7525 4225 50  0000 C CNN
F 2 "" H 7525 4375 50  0001 C CNN
F 3 "" H 7525 4375 50  0001 C CNN
	1    7525 4375
	1    0    0    -1  
$EndComp
Wire Wire Line
	7525 4325 7525 4375
$Comp
L R R102
U 1 1 642C522C
P 8300 3100
F 0 "R102" V 8380 3100 50  0000 C CNN
F 1 "390" V 8300 3100 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 8230 3100 50  0001 C CNN
F 3 "" H 8300 3100 50  0001 C CNN
F 4 "603-AC0603JR-07390RL" V 8300 3100 60  0001 C CNN "Mouser Part Number"
	1    8300 3100
	0    1    1    0   
$EndComp
$Comp
L R R101
U 1 1 642C53B6
P 8275 4025
F 0 "R101" V 8355 4025 50  0000 C CNN
F 1 "390" V 8275 4025 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 8205 4025 50  0001 C CNN
F 3 "" H 8275 4025 50  0001 C CNN
F 4 "603-AC0603JR-07390RL" V 8275 4025 60  0001 C CNN "Mouser Part Number"
	1    8275 4025
	0    1    1    0   
$EndComp
Connection ~ 8050 3100
Connection ~ 8025 4025
$Comp
L LED D101
U 1 1 642C5EE3
P 8425 3725
F 0 "D101" H 8425 3825 50  0000 C CNN
F 1 "RX" H 8425 3625 50  0000 C CNN
F 2 "LEDs:LED_0603" H 8425 3725 50  0001 C CNN
F 3 "" H 8425 3725 50  0001 C CNN
F 4 "710-150060YS75000" H 8425 3725 60  0001 C CNN "Mouser Part Number"
	1    8425 3725
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8425 3875 8425 4025
$Comp
L +5V #PWR017
U 1 1 642C62DD
P 8425 3525
F 0 "#PWR017" H 8425 3375 50  0001 C CNN
F 1 "+5V" H 8425 3665 50  0000 C CNN
F 2 "" H 8425 3525 50  0001 C CNN
F 3 "" H 8425 3525 50  0001 C CNN
	1    8425 3525
	1    0    0    -1  
$EndComp
Wire Wire Line
	8425 3525 8425 3575
$Comp
L LED D102
U 1 1 642C64EA
P 8475 2775
F 0 "D102" H 8475 2875 50  0000 C CNN
F 1 "TX" H 8475 2675 50  0000 C CNN
F 2 "LEDs:LED_0603" H 8475 2775 50  0001 C CNN
F 3 "" H 8475 2775 50  0001 C CNN
F 4 "710-150060SS75000" H 8475 2775 60  0001 C CNN "Mouser Part Number"
	1    8475 2775
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR018
U 1 1 642C6635
P 8475 2525
F 0 "#PWR018" H 8475 2375 50  0001 C CNN
F 1 "+5V" H 8475 2665 50  0000 C CNN
F 2 "" H 8475 2525 50  0001 C CNN
F 3 "" H 8475 2525 50  0001 C CNN
	1    8475 2525
	1    0    0    -1  
$EndComp
Wire Wire Line
	8475 2925 8475 3100
Wire Wire Line
	8475 3100 8450 3100
Wire Wire Line
	8475 2525 8475 2625
$EndSCHEMATC
