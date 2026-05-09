**Button Matrix**

I am currently making a game using Arduino Nano, LED matrix and button matrix. The game name is "_Find a path_". In this game for the first 5 seconds there will be some red(lava) dots will appear then disappear. After that green dots appear and we need to make a path between the 2 green dots without touching the lava dots(we need to memorize the positions).

<img width="2296" height="4080" alt="image" src="https://github.com/user-attachments/assets/e78204c4-8cc3-4b3c-bcc7-f904d572616a" />
<img width="2296" height="4080" alt="image" src="https://github.com/user-attachments/assets/8e7140f9-f356-40a0-a5ce-ed5d55998739" />
<img width="2296" height="4080" alt="image" src="https://github.com/user-attachments/assets/674d7188-9005-4abf-bcc0-9096406a9ad7" />
<img width="2296" height="4080" alt="image" src="https://github.com/user-attachments/assets/700e1acb-6be7-405a-9a16-a1f8a1ab2723" />
<img width="2296" height="4080" alt="image" src="https://github.com/user-attachments/assets/41a34e78-2b3f-47ab-b829-6a9aad551360" />

I have an LED matrix which is currently 04 x 04. But want to change to 08 x 08 for more gaming experience.

It is currently looking like this:

<img width="2296" height="4080" alt="image" src="https://github.com/user-attachments/assets/e78204c4-8cc3-4b3c-bcc7-f904d572616a" />

So, I saw a need for 08 x 08 button matrix.
Here is the schematic

<img width="519" height="451" alt="image" src="https://github.com/user-attachments/assets/c37d549f-5273-4e04-b5d0-0dcfffbfbcd1" />

Here is the PCB 

<img width="507" height="378" alt="image" src="https://github.com/user-attachments/assets/55b59057-596c-4e8d-8ef4-252e390fad47" />

Here is the 3D design

<img width="584" height="401" alt="image" src="https://github.com/user-attachments/assets/1fe5e939-f5dd-4b5e-9ae2-aeff46846202" />

This is a single layered PCB. 

Used F.Cu for route tracking, F.Silkscreen for labelling and Edge.Cuts for outline.

| Item No. | Part Name        | Description              | Quantity | Unit | Total Cost(INR) | Links                                                                                                                                   |
|----------|------------------|--------------------------|----------|------|-----------------|-----------------------------------------------------------------------------------------------------------------------------------------|
| 1        | 12mm x 12mm Tactile push button   | For pressing     | 64        | pcs  | 604             | https://www.amazon.in/gp/product/B07NCZJX3M/ref=ox_sc_act_title_1?smid=AJ6SIZC8YQDZX&psc=1                          |                                              |
| 2        | Header Pins (2.54mm)| For attaching on the PCB         | 1        | pcs  | 135              | https://www.amazon.in/Plated-2-54mm-Header-Single-Straight/dp/B09HGTM3PS/ref=sr_1_5?sr=8-5    |
| 3        | PCB printing service | To order the PCB         | 5        | pcs  | 3770              | https://cart.jlcpcb.com/quote/gerberviewThree/?qs=6395cc0f3cbd44e48086e7938acfc41c_1_0_1_0_0.html    |
