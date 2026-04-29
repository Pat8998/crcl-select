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
- move all files to
  ```
  ~/.config/crcl-select/
  ```
- run build.sh
- run install.sh 
- Now everything is installed !

## Usage
 - Create a `whatever.json` under `~/.config/crcl-select/`
   - a template named `toolbox.json` is here to help you ! Find it under `/etc/crcl-select/`
   - `icon` field is for the icon, duh
     - Plain text, emojis, nerd-fonts
     - if you add $# at the beginning it will be interpreted by bash :) (see example)
   - `command` field wiil be executed !
     - if a key is pressed it will be run under `~/.config/crcl-select/`
     - if the circle is closed by the close command, it will be run under `~/`
     - I'm too lazy to search why, but I guess this is a way to get wich way the command was pushed. use cd; if you're unhappy with it
 - Open a circle with
   ```~/.config/crcl-select/c-select open {name-of-your-json}```
 - Close the circle and execute the corresponding action (to your pointer location) with
   ```~/.config/crcl-select/c-select close {name-of your json}```
 - or press a number 0-9 to execute the action
 - Example : in your `hyprland.conf`
   ```
   bind =		$mainMod, A, exec, ~/.config/crcl-select/c-select open whatever.json
   bindr =	$mainMod, A, exec, ~/.config/crcl-select/c-select close whatever.json
   ```
   (I recommend one key shortcut, do as you want)

## Theming
 - Under `.config/crcl-select/theme.json`, put your new theme as an entry (or modify mines, I don't care).
 - In your open call, you can specify a theme name. If not specified, the default theme (in the "default" field in the config file) will be used.
 - If `theme.json` is misread, fallback to piink theme (hardcoded in C).  

## Features-request

Well, I'm in studies so basically if you want to do smth you'd have to do it yourselves :(
