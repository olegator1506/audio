#!/bin/sh
RemoteTargetDir=/home/artem/work/audio/opi/progs/dac-ctrl
TargetHost=pi2
GDBServerPort=1025
ProjectName=dac-ctrl
OutputFile=./Debug/${ProjectName}
rsync -avr src main.cpp ${TargetHost}:${RemoteTargetDir}
ssh ${TargetHost} "cd ${RemoteTargetDir}&&make -f dac-ctrl.mk"
#ssh ${TargetHost} "gdbserver --once :1025 ${RemoteTargetDir}/Debug/${ProjectName}"
ssh ${TargetHost} "${RemoteTargetDir}/Debug/${ProjectName}"
