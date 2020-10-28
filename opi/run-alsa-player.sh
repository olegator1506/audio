#!/bin/sh
session_name=myalsa
device=hw:0,0
/usr/bin/alsaplayer --session-name $session_name --device $device -i daemon --verbose
