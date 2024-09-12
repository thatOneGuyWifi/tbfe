# tbfe - Text-Based File Explorer

tbfe is a file explorer I made (with the help of chatgpt) to test my coding skills since I haven't coded for a while. tbfe is pretty lightweight (I guess). Tbfe is very simple and has commands you generally need for a file explorer (e.g creating files, directories, changing directories, removing files or directories)

## Features

- `help`: shows all the command for tbfe
- `ls`: lists all the files and directories in the current directory
- `cr`: creates a file or directory
- `goto`: changes the directory (use .. to go back a directory and - to the previous directory you were in)
- `rn`: renames a file or directory
- `mv`: moves a file or directory to another directory
- `exit`: exits tbfe
- `clear`: clears all the output
- `rm`: removes a file or directory 

## Installation

clone the repository and compile the cpp file with GCC (make sure it's GCC 14.2.1 or higher)

```bash
git clone https://github.com/thatOneGuyWifi/tbfe.git
cd tbfe
g++ tbfe.cpp -o tbfe
```
Optionally you can make an alias for the compiled code 

Example:
```bash
alias tbfe=/home/user/tbfe/./tbfe
```
change /home/user/tbfe/ to the path the compiled code is in

## Running tbfe

To run tbfe, type `./tbfe` (or the name of the compiled code). If you made an alias type the name of the alias (e.g `tbfe`)

## License

This project is licensed under the GNU General Public License v3.0 (GPL v3.0)

# Contributing

You can contribute to the project if you want
