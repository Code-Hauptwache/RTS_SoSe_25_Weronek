# How to monitor processes and thread?

following programm has been executed
```bash
zaka@zakaBouj:/mnt/c/Users/zb200/Documents/GitHub/RTS_SoSe_25_Weronek/Linux/05_Execution_Times_2$ ./load MyLabel 10 15 2000000000
./load MyLabel   0 1750776720 506046606
./load MyLabel    1 1750776721 631641045
./load MyLabel    2 1750776722 745157413
./load MyLabel    3 1750776723 856734379
./load MyLabel    4 1750776724 969497903
./load MyLabel    5 1750776726  75214369
./load MyLabel    6 1750776727 183575649
./load MyLabel    7 1750776728 292967006
./load MyLabel    8 1750776729 415773304
./load MyLabel    9 1750776730 530860335
./load MyLabel   10 1750776731 643975887
```

a) Looking for detailed process information while `./load` is running

```bash
zaka@zakaBouj:/mnt/c/Users/zb200/Documents/GitHub/RTS_SoSe_25_Weronek/Linux/06_Monitoring_of_Processes_and_Threads$ ps -u $(whoami) -o ppid,pid,psr,sgi_p,pcpu,comm,policy,rtprio,pri,nice,time,c,f,wchan,cmd,pmem,maj_flt,min_flt,sz
   PPID     PID PSR P %CPU COMMAND         POL RTPRIO PRI  NI     TIME  C F WCHAN  CMD                         %MEM  MAJFL  MINFL    SZ
    405     406  14 *  0.0 bash            TS       -  19   0 00:00:00  0 4 do_wai -bash                        0.0      4   3922  1715
      1     460  15 *  0.0 systemd         TS       -  19   0 00:00:00  0 4 -      /lib/systemd/systemd --user  0.0      0   1815  4301
    460     464  11 *  0.0 (sd-pam)        TS       -  19   0 00:00:00  0 5 -      (sd-pam)                     0.0      0     52 42305
    460     474   0 *  0.0 pipewire        TS       -  19   0 00:00:00  0 0 -      /usr/bin/pipewire            0.0     39    667  8564
    460     475  13 *  0.0 pipewire-media- TS       -  19   0 00:00:00  0 0 -      /usr/bin/pipewire-media-ses  0.0     39    664  4607
    407     478   4 *  0.0 bash            TS       -  19   0 00:00:00  0 4 core_s -bash                        0.0      0   1473  1564
    460     495   0 *  0.0 dbus-daemon     TS       -  19   0 00:00:00  0 0 -      /usr/bin/dbus-daemon --sess  0.0      0    334  2075
    406    3579   3 *  0.2 load            TS       -   4  15 00:00:01  0 0 do_sig ./load MyLabel 10 15 200000  0.0      1     86   694
   3913    3919  15 *  0.0 bash            TS       -  19   0 00:00:00  0 4 do_wai -bash                        0.0      0   3052  1586
    406    7140   4 4 89.5 load            TS       -   4  15 00:00:05 89 0 -      ./load MyLabel 10 15 200000  0.0      0     84   694
   3919    7163   8 8  0.0 ps              TS       -  19   0 00:00:00  0 0 -      ps -u zaka -o ppid,pid,psr,  0.0      0    192  1871
zaka@zakaBouj:/mnt/c/Users/zb200/Documents/GitHub/RTS_SoSe_25_Weronek/Linux/06_Monitoring_of_Processes_and_Threads$ 
```

b) (some text)
```bash
zaka@zakaBouj:/mnt/c/Users/zb200/Documents/GitHub/RTS_SoSe_25_Weronek/Linux/06_Monitoring_of_Processes_and_Threads$ pstree -acghlpsUu
systemd,1,1
  ├─agetty,279,279 -o -p -- \\u --noclear --keep-baud console 115200,38400,9600 vt220
  ├─agetty,286,286 -o -p -- \\u --noclear tty1 linux
  ├─avahi-daemon,168,168,avahi
  │   └─avahi-daemon,229,168
  ├─cron,177,177 -f -P
  ├─dbus-daemon,179,179,messagebus --system --address=systemd: --nofork --nopidfile --systemd-activation --syslog-only
  ├─init-systemd(Ub,2,
  │   ├─SessionLeader,404,404
  │   │   └─Relay(406),405,404
  │   │       └─bash,406,406,zaka
  │   │           ├─load,3579,3579 MyLabel 10 15 2000000000
  │   │           └─load,7500,7500 MyLabel 10 15 2000000000
  │   ├─SessionLeader,3912,3912
  │   │   └─Relay(3919),3913,3912
  │   │       └─bash,3919,3919,zaka
  │   │           └─pstree,7523,7523 -acghlpsUu
  │   ├─init,6, --control-socket 6 --log-level 4 --server-fd 7 --pipe-fd 9 --log-truncate
  │   │   └─{init},7,
  │   ├─login,407,407 -f
  │   │   └─bash,478,478,zaka
  │   └─{init-systemd(Ub},8,
  ├─networkd-dispat,187,187 /usr/bin/networkd-dispatcher --run-startup-triggers
  .
  .
  .
```

c) 
```bash
zaka@zakaBouj:/mnt/c/Users/zb200/Documents/GitHub/RTS_SoSe_25_Weronek/Linux/06_Monitoring_of_Processes_and_Threads$ ps -ef | grep $(whoami)
avahi        168       1  0 16:34 ?        00:00:00 avahi-daemon: running [zakaBouj-2.local]
zaka         406     405  0 16:34 pts/0    00:00:00 -bash
zaka         460       1  0 16:34 ?        00:00:00 /lib/systemd/systemd --user
zaka         464     460  0 16:34 ?        00:00:00 (sd-pam)
zaka         474     460  0 16:34 ?        00:00:00 /usr/bin/pipewire
zaka         475     460  0 16:34 ?        00:00:00 /usr/bin/pipewire-media-session
zaka         478     407  0 16:34 pts/1    00:00:00 -bash
zaka         495     460  0 16:34 ?        00:00:00 /usr/bin/dbus-daemon --session --address=systemd: --nofork --nopidfile --systemd-activation --syslog-only
zaka        3579     406  0 16:44 pts/0    00:00:01 ./load MyLabel 10 15 2000000000
zaka        3919    3913  0 16:45 pts/2    00:00:00 -bash
zaka        7961     406 97 16:58 pts/0    00:00:04 ./load MyLabel 10 15 2000000000
zaka        7982    3919  0 16:58 pts/2    00:00:00 ps -ef
zaka        7983    3919  0 16:58 pts/2    00:00:00 grep --color=auto zaka
zaka@zakaBouj:/mnt/c/Users/zb200/Documents/GitHub/RTS_SoSe_25_Weronek/Linux/06_Monitoring_of_Processes_and_Threads$ 
```