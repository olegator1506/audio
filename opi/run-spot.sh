#!/bin/sh
DAEMON_CMD="/home/artem/work/audio/opi/spotifyd"
USERNAME="ocbpkrf8jrtgb2vapp6qhnjqy"                                       
PASSWORD="Cg0t1Xdz"                                                        
PID_FILE="/home/artem/work/audio/opi/var/spotifyd.pid"                     
DEVICE_NAME="myDAC-test"                                                   
SOUND_DEVICE="hw:1,0"
BITRATE="320"
BACKEND="alsa"
HOOK=/home/artem/work/audio/opi/progs/spotify-hook/spotify-hook.php
#$DAEMON_CMD --username $USERNAME --password $PASSWORD --pid $PID_FILE --device-name $DEVICE_NAME --device $SOUND_DEVICE --no-daemon --on-song-change-hook $HOOK
$DAEMON_CMD --username $USERNAME --password $PASSWORD --pid $PID_FILE --device-name $DEVICE_NAME --device $SOUND_DEVICE --no-daemon 