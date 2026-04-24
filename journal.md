**Day 1 - Getting the schematic** _Hours spent: 6 hours_

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


**Day 2 - Making the PCB** _Hours spent: 7 hours_

I first updated the schematic into the PCB editor.

Then got to know that the Column pins had no way of connection.

<img width="256" height="395" alt="image" src="https://github.com/user-attachments/assets/d5f091bb-049f-42e8-88b3-b370d5f89c01" />

So, I asked for help in #fallout-help, it is hardware program and many people would have knowledge of making PCB's.

They guided me to how to solve the problem. For this problem to be solved I had to change the pads. Then did changes to every other switch.

Credits to @Gwendal Briantais for helping me with this problem. Wouldn't have continued this project if the problem was not fixed.

Also I would have told the errors that I got while updating the PCB from schematic but realized that after we finished discussing.

Then I started the most tedious part which is to assemble everything out. Right now it looked like this

<img width="545" height="432" alt="image" src="https://github.com/user-attachments/assets/1e27a1d4-48cc-4285-bb53-c883d3fa18e3" />

But I realised I do not need diodes in my project literally because in my case I do not need multi detection keys. Credits to my father mentioning it out while I was doing it.

So removed diodes from schematic and edited it to PCB editor.

Started assembling everything out which took a pretty much 4 hours to do.

And in the end it looked like this:

<img width="741" height="508" alt="image" src="https://github.com/user-attachments/assets/cc20c4f8-55e1-42f5-a606-92806f8e49eb" />

For route racking I used F.Cu, for writing text I used F.Silkscreen and edge.cuts for outline. The route tracking looks sick though to be honest.

Down is the 3D image of it:

<img width="812" height="419" alt="image" src="https://github.com/user-attachments/assets/9ed6195c-753e-4212-ae82-3b43af4fd4b4" />

Finally ending the project <3......
