# LandTiger_Tetris
Simple Tetris clone developed for a LandTiger LPC1768 board. Extra points project for a Computer Architectures course at Politecnico di Torino. Developed with Keil µVision. The colorscheme is [Catppuccin Mocha](https://catppuccin.com/palette/).
## Installation
To use, clone this repository:
```
git clone https://github.com/leeeeeeeeeem/LandTiger_Tetris
```
Then open the project file (sample.uvprojx) inside the Keil µVision IDE. Connect the board to your computer, build the code and load it onto the board.
## Usage
The game starts in a paused state, press KEY1 to unpause. Move Tetrominoes left and right with the joystick and rotate them with joystick up. 
By default, Tetrominoes move at the speed of 1 block per second, soft drop (2 blocks per second) functionality is activated when holding joystick down.
Hard drop (Tetromino drops instantly) functionality is activated by pressing KEY2. 
When the game ends, the high score is updated and the game is reset back to the original paused state.
## Gameplay
https://github.com/user-attachments/assets/555a8e00-92a8-41ce-9767-3d75a529b781

