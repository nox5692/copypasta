# copypasta
#### An extended Linux terminal copy-paste tool

## [NOTICE]
**Current version does not have complete `build.sh` - does not create global binary!!!**

### Motivation
I have always found the `cp` Linux command underwhelming. It has always come far second to the traditional Ctrl+C Ctrl+V GUI approach, thus slowing down my workflow tremendously. The world needs a versatile CLI copy-paste tool, with its own clipboard registers and memory. And thus, the idea for **copypasta** was born.

### Installation and build
1. Clone this repository
```bash
git clone https://github.com/nox5692/copypasta.git
```
2. Install and configure
```bash
cd copypasta;
./build.sh;
```
- **IMPORTANT: In the current version 0.1, you need to change the `PASTA_GLOBAL_PATH` variable for the registers to work!**
3. Run
- copy
```bash
pasta -c[[0..9]] <files>
```
- paste
```bash
pasta -[[0..9]]
```
- list clipboard registers
```bash
pasta --list
```
- clear clipboard
```bash
pasta --clear
```
