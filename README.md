# Embedded-Sys-Lab
2110366 Enbedded System Lab


## Serial Terminal
MacOS

``` zsh
screen /dev/tty.usbmodem1203 115200, onclr
```
Exit Screen: **Ctrl+A** then **Ctrl+\\**

```zsh
ls /dev/tty.* #search for port
screen //port// 115200 #connect to port with buad rate
screen -ls #list all active serial port
screen -X -S //identifier// quit #quit that serial port
```
