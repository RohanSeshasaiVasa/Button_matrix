Day-1 Getting the schematic
Took the components needed - Tactile push button, Diodes(1N4148) and pin header 01 x 08.

Made duplicates of the buttons and diodes and assembled them. Connected each switch's pad 1 to 1 diode. For all 64 switches.

<img width="422" height="389" alt="image" src="https://github.com/user-attachments/assets/ecd06a0e-0ec3-46e4-b205-2f4f2ca71f3c" />

Connected the header pins in series with switches for rows and columns(very tedious lol for 64 switches). For this I had to connect the Row pins to the diodes which goes to the switch.

<img width="96" height="561" alt="image" src="https://github.com/user-attachments/assets/9051f520-209e-4b42-adbb-fff173791578" />

For the column, connected the Column pins to pad 4 then went in series(pad 3 to pad 4).

<img width="684" height="105" alt="image" src="https://github.com/user-attachments/assets/81c83301-e81a-4ad8-a309-b9da2d914f09" />

Did the same for all 8 rows and columns and finally got the schematic result.

<img width="742" height="570" alt="image" src="https://github.com/user-attachments/assets/c13b7413-28c2-4a49-8a5c-403b4a677eec" />

Ran the ERC to check for errors, I got many errors which stated that there were many unconnected pins, so I just labeled them as no connect.

This was such a very huge PCB, but needed for the feel to play the game.

Finally ran the ERC and got no errors and logging of the day.
