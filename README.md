# ATMEGA32U2-Rock-Paper-Scissors
###### Course Project for ENCE260
A Rock Paper Scissors game written for the ATmega32u2 microcontroller, using the UC Fun-Kit 4 embedded
board.

Written in part with Juliet Samandari.

To play this game with a UCFK4, navigate to your clone of the funkit library, and place this two layers deep.
e.x. /ence260-ucfk4/\*/\*/game.c
This is to ensure the makefile can find the relevant dependencies.

###### The Fun-Kit
The UCFK4 was designed by Philipp Hof and Michael Hayes, and the implementation depends on multiple
drivers, and utility programs. 

The UCFK4 has an ATmega32u2 microcontroller, a reset push button, a general-purpose pushbutton, a five-way navigation switch, a green LED that indicates if power is on, a user switchable blue LED, a seven by five dot-matrix display, an infrared LED, a 36 kHz infrared receiver, and a USB connector. The USB connector provides 5 V to run the microcontroller and to allow programs to be up-loaded. The ATmega32U2 microcontroller in the UCFK4 uses the AVR DFU bootloader.

###### Game README
A copy of the [games's README](/docs/README.txt) on how to play:
1)  You will first have the title screen of 'ROCK PAPER SCISSORS PRESS START' displayed. Push the navswitch to move to the next phase of game play
2)  The options of first to three, first to five and first to seven are then displayed. 
    You can toggle between the options by pressing the navswitch north or south (up or down if the USB connector is at the top). 
3)  The first person to push the navswitch selects the number of points to play until. This moves both players to the next phase of game play.
4)  You can then toggle between R, P and S by pressing the navswitch north or south. To select push the navswitch.
5)  Your screen will then display whether you have won, lost or tied. Push the navswitch to display the score.
6)  The score will display your score first and your partner's score second. In the style - your score to partner's score.
7)  To progress to the next round push the navswitch twice. Whoever pushes the navswitch a second time first takes you both back to step 4.
8)  When either you or your partner have achieved the selected number of points the game is over and the final score is displayed.
9)  To start a new game push the navswitch. 

At any point in the game you can push the button s3 to restart the game.
You can also press the navswitch east(right if the USB connector is at the top) and then push the navswitch to display the score at any time. Push the navswitch twice to return to gameplay. 

