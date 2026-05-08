# A circle widget
 - Made for Hyprland btw 
 - made with [eww](https://github.com/elkowar/eww)
 - written in C / yuck / css
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/3d6bfeea-0091-43c6-af57-352f08cbb68c" />

## Download

### Arch :
```
yay crcl-select
```
[AUR Link](https://aur.archlinux.org/packages/crcl-select)

## Build
 - clone with
   ```
   git clone https://github.com/Pat8998/crcl-select/
   ```
- run build.sh
- run install.sh 
- move config files with
  ```
  mkdir -p ~/.config/crcl-select 
	cp /etc/crcl-select/* ~/.config/crcl-select
  ```
- Now everything is installed !

## Usage
 - Create a `whatever.json` under `~/.config/crcl-select/`
   - a template named `toolbox.json` is here to help you ! Find it under `/etc/crcl-select/`
   - `icon` field is for the icon, duh
     - Plain text, emojis, nerd-fonts
     - if you add $# at the beginning it will be interpreted by bash :) (see example)
   - `command` field wiil be executed !
     - if a key is pressed it will be run under `/usr/share/crcl-select`
     - if the circle is closed by the close command, it will be run under `~/`
     - ~~I'm too lazy to search why~~ This is because the way I launch the commands, but I guess this is a way to get which way the command was pushed. use cd; if you're unhappy with it
 - Open a circle with
   ```
   crcl-select open {name-of-your-json}
   ```
 - Close the circle and execute the corresponding action (to your pointer location) with
   ```
   crcl-select close {name-of your json}
   ```
 - or press a number 0-9 to execute the action
 - Example : in your `hyprland.conf`
   ```
   bind =		$mainMod, A, exec, crcl-select open   whatever.json
   bindr =	$mainMod, A, exec, crcl-select close  whatever.json
   ```
   (I recommend a shortcut with a single key like super, do as you want)

## Theming
 - Under `.config/crcl-select/theme.json`, put your new theme as an entry (or modify mines, I don't care).
 - You can copy the default config file from `/etc/crcl-select/`
 - In your open call, you can specify a theme name. If not specified, the default theme (in the "default" field in the config file) will be used.
 - If `theme.json` is misread, fallback to piink theme (hardcoded in C).  

## To-do list 
###### *Nothing on the to-do list for now!*


## Features-request

Well, I'm in studies so basically if you want to do smth you'd have to do it yourselves :(
