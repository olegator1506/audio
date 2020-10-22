#!/usr/bin/php
<?php

function saveLog($mess) {
        $fl = fopen('/home/artem/work/audio/opi/var/spotify-hook.log',"a");
        if(!$fl) {
            echo "Can not open log file";
            exit();
        }
        fwrite($fl,"{$mess}\n");
        fclose($fl);
    }


function selectImage($images){
    $sizes = [];
    foreach($images as $image) {
        $size = $image['height'] * $image['width'];
        if(($size < 100000) and ($size > 10000)) return $image['url'];
    }
    $image = array_shift($images);
    return $image['url'];
}
chdir(dirname(__FILE__));
include 'config.inc';
require_once 'classes/spotify-client.inc';


$evt = getenv('PLAYER_EVENT');
$trackId = getenv('TRACK_ID');
$oldTrackId = getenv('OLD_TRACK_ID');
switch($evt) {
    case 'stop':
        $cmd = 'pub_spotify_stop';
        break;
    case 'start':
        $cmd = 'pub_spotify_start';
    case 'change':
        $cmd = 'pub_spotify_change';
        break;
    default:
        $cmd = false;
        break;
}

if(!$cmd) return;
$client = new TSpotifyClient($config);
$trackInfo = $client->getTrackInfo($trackId);
if(!$trackInfo) retrurn;
$artistName = "";
if(is_array($trackInfo['artists'])){
    $artist = array_shift($trackInfo['artists']);
    $artistName = @$artist['name'];
}
$img = false;
if(is_array($trackInfo['album']['images'])){
    $img = selectImage($trackInfo['album']['images']);
}
$duration = $trackInfo['duration_ms'] / 1000;
$durationS = sprintf("%02d:%02d",$duration / 60, $duration % 60);
$client->queryServer($config['NOTIFY_URL'],[
    'cmd'=>$cmd,
    'track_id'=>$trackId,
    'album'=>$trackInfo['album']['name'],
    'artist'=>$artistName,
    'track_name'=>$trackInfo['name'],
    'image'=>$img,
    'duration_string'=>$durationS,
    'duration'=>$duration
]);


?>