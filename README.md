# Yes? No? Maybe?
Arduino based Probabilistic/Random trigger with 1 input & 5 outputs, dedicated to modular synthesizers.

## Usage
There's 1 gate input and 5 gate outputs. <br />
When gate signal comes to the input, it is distributed to the 5 outputs following the chance setted by its dedicated knob. <br />
When knob is at 0%, there's no chance that the output will reproduce the gate signal. <br />
When knob is at 100%, there's 100% chance that the output will reproduce the gate signal. <br />

## Pattern mode
I also added a "Pattern mode" switch. It allows to choose between Random & Pattern mode. <br />
Random mode is the normal mode. <br />
In "Pattern mode", each of the output will follow a rythmic pattern. The knob will let you choose the pattern. <br />
There's 62 different patterns available, with various lengths. <br />
This is very helpful in order to create polyrythmic beats. <br />

## Components
6x 1k resistor <br />
1x 100k resistor <br />
5* LED (red) <br />
5* 10k potentiometer <br />
2* 1N5817 (Shottky diode) <br />
1* TL074 <br />
1* TL072 <br />
4* 100nF <br />
2* 10uF <br />
1* switch <br />
1* arduino (nano, but others might work, give it a try and tell me!) <br />
6* jack socket (1 in, 5 out) <br />

Be sure that all jack sockets grounds are connected together ! <br />
TL072 & TL074 op-amps works with 12v/-12v, which is very common in modular system. If you want to make this project with an USB or 9v power socket, you will have to choose other op-amp in order to buffer the gate outputs. <br />


## Schematic
![Schematic](https://raw.githubusercontent.com/alexiszbik/yesnomaybe/main/schematic.png)
