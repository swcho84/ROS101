## udev rule implementation
```
$ sudo udevadm control --reload-rules && udevadm trigger
$ sudo reboot (or just USB device disconnected and connected)
```
## check the status
```
$ ls -al /dev/(designated name)
```


