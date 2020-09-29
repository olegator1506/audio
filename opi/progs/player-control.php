<?php
/**
 * Created by PhpStorm.
 * User: artem
 * Date: 28.09.20
 * Time: 21:44
 */
$incPath = '.:'.__DIR__ . '/../lib/php/';
ini_set('include_path',$incPath);
include __DIR__."/../config.inc";
require_once "player.inc";
$player = new Player();

$cmd = $argv[1];

switch($cmd) {
    case 'load':
        $player->load();
        break;
    case 'quit':
        $player->quit();
        break;
    case 'start':
        $player->start();
        break;
    case 'next':
        $player->next();
        break;
    case 'status':
        $player->status();
        break;
    case 'addfile':
        $player->addFile($argv[2]);
        break;

}