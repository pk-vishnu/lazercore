![lazercore1](https://github.com/user-attachments/assets/e7b6cfb6-69a9-4dbc-b367-30854e5d35ae)
> [!CAUTION]
> This is a custom firmware that could break your keyboard.
>
> 🛑 **Use at your own risk!** 🛑

## Features  

### VIA Enabled  
Easily remap keys, configure layers, and customize RGB lighting using the [Via Configurator](https://usevia.app/).  

### CapsWord  
Type a word in all caps by pressing `Left Shift + Right Shift`.  

### Sentence Case  
Toggle sentence case mode with `Fn + Caps Lock`. Automatically capitalizes the first letter of each sentence.  

### Autocorrect  
Toggle Autocorrect with `Fn + F3`.  
- Corrects common typos using a dictionary created by [@gargum](https://github.com/gargum).  

### Game Mode  
Activate Game Mode with `Fn + Right Shift + G`. Features include:  
- **SOCD Filtering**: Prioritizes the latest input between two conflicting keys for faster directional changes.  
- **Custom RGB Matrix**: Highlights WASD keys with adjustable RGB modes.  
- **Windows Key Lock**: Blocks the `LGUI` (Windows) key to prevent interruptions.  

### Audio Visualizer Mode (Layer 3) (Currently non-functional, rewrite in progress)
Activate with `Fn + Right Shift + Volume Knob`.  
- Real-time, reactive audio visualization powered by [Lazersync](https://github.com/pk-vishnu/lazersync).  

### Type Alchemy  
Toggle Type Alchemy with `Fn + F1`.  
- Automatically convert words into symbols using a customizable map. For example, typing "infinity" converts to `∞`.  
- Switch between Unicode modes for Windows ([WinCompose](https://github.com/samhocevar/wincompose) required), Linux, and macOS with `Fn + F2`.  
- Use the public API in `type_alchemy.h` to expand functionality.  

### Light Indicators  
Visual indicators show the currently active layer and available function keys.  

### Knob Controls  
- **Layer 0**: Volume control  
- **Layer 1**: Screen brightness  
- **Layer 2**: Media fast-forward/rewind  

### DFU Mode  
Enter bootloader mode for flashing firmware by pressing `Fn + Shift + Esc`.  

### Clear EEPROM  
Clear the keyboard's EEPROM memory with `Fn + Space`.  

---

## RGB Controls  

- **Brightness**: Adjust with `Fn + Up/Down Arrows`.  
- **Effect Speed**: Adjust with `Fn + Left/Right Arrows`.  
- **RGB Mode**: Cycle modes with `Fn + \` (Backslash).  
- **Further Customization**: Use the [Via Configurator](https://usevia.app/).  

---

## Getting Started  

### Prerequisites  

#### To Flash Firmware  
1. Install [QMK Toolbox](https://github.com/qmk/qmk_toolbox) to flash firmware onto your keyboard.  

#### To Compile Firmware  
1. Set up your [QMK environment](https://docs.qmk.fm/newbs_getting_started) to compile and modify the firmware source code.  

---

### Flashing the Firmware  

1. **Download the Firmware**:  
   - Clone this repository or download the `.hex` file from the `Compiled` folder.  

2. **Flash the Firmware**:  
   - Enter DFU mode by pressing `Fn + Shift + Esc`.  
   - Alternatively, press the `ESC` key while plugging in the USB cable, or use the reset button located under the space bar.  
   - Use **QMK Toolbox** to flash the `lazercore.hex` file to your keyboard.  
   
---

### Compiling the Firmware  

1. Copy the `RK75` folder to the `keyboards` folder in your QMK firmware environment.  
2. Run the following command to compile the firmware:  
     ``` qmk compile -kb RK75 -km lazercore ``` (or) ```make RK75:lazercore -j``` 

## Contributing  

Contributions, bug reports, and feature requests are welcome!  

---

## Acknowledgments  
- Special thanks to [@sdk66](https://github.com/sdk66), [@snakkarike](https://github.com/snakkarike), [@irfanjmdn](https://github.com/irfanjmdn), and [@iamdanielv](https://github.com/iamdanielv) for their contributions to RK keyboards, providing a solid foundation for this project.
- Grateful to the [QMK Community](https://qmk.fm/) for their extensive documentation and support.  
---  
