---
title: "kyps75 build journal"
author: "Pratham Rupera"
description: "A comprehensive log of designing a custom 75% mechanical keyboard featuring dual rotary encoders and an OLED display, and all the troubleshooting along the way."
created_at: "2026-08-20"
---

# august 20: deciding on the layout and keymap
So I started the project today originally thinking I'd go with a standard 60% layout. But I quickly realized how much I actually need dedicated arrow keys, navigation keys, and macro controls for when I'm coding and drawing. I decided an exploded 75% layout would work best. I spent hours tweaking the key placements in Keyboard Layout Editor (KLE), trying to figure out the spacing for dual rotary encoders (one for volume, one for brush size and timeline scrolling) and a 0.91" OLED display. I also had to spend a lot of time double-checking the keycap row profiles (R1 to R4) to make sure non-standard sizes, like the 1.75u right shift and 1u bottom-row modifiers, wouldn't cause fitment issues with standard keycap sets.
![layout planning diagram](keyboard-layout.png)
**total time spent: 2 Hours**

# august 21: plate outline and mounting styles
I started off by exporting the KLE raw JSON data into the swillkb plate builder to generate the preliminary DXF vector file for the top plate switch matrix. I had a long debate with myself over the mounting styles. While a gasket mount provides better sound dampening, a sandwich top mount is just far more forgiving for 3D printing and gives better structural rigidity (and saves me a ton of time on designing gasket tabs). I modified the switch cutout corners from crisp right angles to 0.5mm fillets so they accommodate the FDM 3D printer nozzle radii, which should prevent stress fractures around the perimeter. Then I exported the updated CAD files for testing.
![plate vector draft](dxf.png)
**total time spent: 2 Hours 30 Minutes**

# august 22: doing the schematics and pin mapping
Today I opened KiCad to begin the electrical schematic capture. I selected the MCU board and mapped out all the pin requirements. An 82-key matrix in a 6-row by 15-column layout needs 21 GPIO pins. The dual EC11 rotary encoders need 2 quadrature signals and 1 push-button pin each (6 pins total), and the I2C OLED screen takes 2 pins (SDA/SCL). Running out of pins is a real worry here! I placed the switch components and wired them up with 1N4148 switching diodes across every single node to prevent ghosting and key rollover. I wired up the initial matrix grid, making absolutely sure to verify the diode polarity because having to desolder 82 backwards diodes later would be awful.
![kicad schematic matrix](schematic_new.png)
**total time spent: 3 Hours 30 Minutes**

# august 23: wiring up the OLED and encoders
I shifted my focus to integrating the peripheral schematics into the main matrix. First, I wired up the I2C bus line for the 128x32 OLED display and added 4.7kΩ pull-up resistors to both the SDA and SCL lines to ensure clean signal transmission. Then, I placed the footprint logic for the two EC11 rotary encoders. I decided to add RC low-pass filter networks (10kΩ resistors and 10nF capacitors) to hardware-debounce the noisy encoder signals before they even reach the MCU pins. Doing hardware debouncing now should save me from writing annoying software debounce code later. Finally, I consulted two friends to review my logic connections and verify I didn't create any voltage rail shorts lol.
![peripheral schematic detail](schematic_new.png)
**total time spent: 3 Hours 30 Minutes**

# august 24: component layout in KiCad
I imported the schematic netlist into KiCad's PCB editor and spent the first two hours just doing manual component arrangement. I placed the 82 switch footprints in a strict 19.05mm x 19.05mm grid alignment so the keycap alignment perfectly matches standard key spacing. I nestled the switch diodes directly underneath each switch footprint to keep the trace lengths as short as possible. Then, I positioned the rotary encoder footprints in the top corners and set the OLED module display window perfectly flush along the upper top bezel. I also made sure to verify the component clear zones so the switch housing clips won't collide with any of the surrounding passive SMD components.
![pcb footprint placement](pcb_new_1.png)
**total time spent: 4 Hours**

# august 25: PCB routing and DRC hell
This was the most intense routing session of the build. I ran traces for the matrix rows and columns on the top layer, while reserving the bottom layer primarily for a solid ground plane. I ran into massive routing congestion near the USB-C cutout and the MCU socket pins. Every time I ran DRC, KiCad suddenly reported clearance errors because my 0.2mm trace widths were overlapping trace-to-pad clearances. I had to manually drop the trace widths down to 0.15mm and reroute the signals around the second rotary encoder footprint. After three full rerouting passes, DRC finally came back with no errors! My eyes definitely hurt after this one.
![pcb trace routing completed](pcb_new_2.png)
**total time spent: 4 Hours 30 Minutes**

# august 27: designing the 3D case
Today I transitioned to 3D CAD modeling to design the main housing. I created a two-piece case design consisting of a top bezel frame and a bottom enclosure tray. I modeled the internal PCB mounting standoffs with pockets for M2 threaded brass inserts. I carefully calculated the wall thickness to a 3.0mm minimum to avoid case flex and resonance, and set an ergonomic typing angle of 6 degrees. I also made sure to add 0.3mm tolerance buffers around all the internal walls. This way, any minor FDM printer expansion won't cause the PCB to bend or bind during installation, which saves me from having to sand PLA later.
![3d case cad model](case_1.png)
**total time spent: 4 Hours 30 Minutes**

# august 28: finishing the CAD and slicer settings
I finalized the top plate CAD enclosure details today. I designed a recessed window frame for the OLED screen so it can sit flush without actually touching the glass face. Then I created the USB-C breakout port cutout on the rear wall, adding chamfered edges for cable connector clearance so it looks clean. Once that was done, I exported all the components as high-density STL files. I imported the models into PrusaSlicer and configured the print settings: 0.2mm layer height, 25% cubic infill for sound resonance tuning, and organic tree supports for the internal overhangs. The project is finally ready for test printing and firmware configuration! :D
![slicer preview and render](case_3.png)
**total time spent: 3 Hours**

# september 9: firmware configuration & speedrunning C
Spent 4 hours today tackling the firmware and honestly, half of that time was just me speedrunning learning C from scratch (because pointers and memory management are actual nightmare fuel). If you don't count the 2 hours I spent staring at C tutorials and documentation in absolute confusion trying to figure out how C even works, the actual time taken to write and test the code was only about 2 hours. I mapped out the 6x15 key matrix, set up the custom keymaps and layer structures for the 75% layout, and configured the quadrature signals for the dual EC11 rotary encoders so they handle master volume and timeline scrolling properly. I also wrote the display driver logic to push status icons and layer info to the 0.91" OLED screen. After fighting a barrage of missing semicolons and compiler errors, I finally got a clean build compiled and ready to flash.
![code.png](firmware.png)
**total time spent: 4 Hours**
