# DarkishTower
An homage to the classic Dark Tower board game written for the Feather S2 microcontroller and an LCD screen
Plays the entire original game, but you'll need to print a game board to go with it.

Video series showing the game and build process:
https://youtu.be/FMZSXwdLvgo

3D Models for the tower:
https://www.printables.com/model/160930-mini-dark-tower

Hardware used:
* FeatherS2: https://www.adafruit.com/product/4769
* LCD Screen: https://www.adafruit.com/product/4311
* Amp & Speaker: https://www.adafruit.com/product/3885

Tested using Arduino IDE versions 1.8.19 and 2.2.1

Board: 
'UM Feather S2' found in the ESP32 Arduino Core (2.0.0 or later)
See https://feathers2.io/ for setup details

Libraries needed:
Adafruit_ST7789
Adafruit_GFX

![PreviewImage](https://github.com/mighty-bean/DarkishTower/blob/main/dark_tower_preview.jpg)

![WiringDiagram](DT_Wiring.png)

Wokwi (online simulator)
-------------------------
You can run the project in Wokwi using an ESP32 dev board and an ST7789 display component. 

**Quick Start:**
1. Clone/fork this repository and open it in Wokwi (Wokwi will auto-detect the `wokwi.json` file).
2. The `wokwi.json` file includes a pre-configured ESP32 dev board wired to an ST7789 display with the correct pin mappings.
3. In the Wokwi editor, add the build flag `-DWOKWI` to the project settings (under the "Project Info" gear icon).
4. Click "Start Simulation" to build and run. The display should render graphically.
5. Open the Serial Monitor in Wokwi to see debug output and game state.

**Manual Setup (if you prefer):**
1. Create a new Wokwi project and select an ESP32 board (e.g., "ESP32 Dev Module").
2. Add an ST7789 display component in the Wokwi editor and wire it to the ESP32 as follows (matches the default pins in the code when `WOKWI` is defined):
	- SCLK -> GPIO18
	- MOSI -> GPIO23
	- CS   -> GPIO5
	- DC   -> GPIO16
	- RST  -> GPIO17
3. Ensure the Adafruit libraries are available in the Wokwi project (Wokwi pulls common Arduino libraries automatically when building).
4. Add `-DWOKWI` to the project's build flags so the code uses the real ST7789 driver.
5. Run the simulation and open the Serial Monitor to see debug output. The display should render graphically in Wokwi.

**SIMULATION Mode (headless/serial-only):**
If you prefer a lighter simulation that logs display actions to Serial instead of rendering graphically, use `SIMULATION` mode by adding `-DSIMULATION` to your build flags. This is useful for quick headless builds and continuous integration.


