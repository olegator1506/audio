<?php
$data=[
  'channels'=>[
		['num'=>0,'name'=>'AUX1','type'=>'AUX','auxNum'=>0,'support_tracks'=>false],
		['num'=>1,'name'=>'AUX2','type'=>'AUX','auxNum'=>1,'support_tracks'=>false],
		['num'=>2,'name'=>'LINE','type'=>'LINEIN','auxNum'=>0,'support_tracks'=>false],
		['num'=>3,'name'=>'ALSA','type'=>'ALSA','auxNum'=>0,'support_tracks'=>true]
  ]
];
header("Access-Control-Allow-Origin: *");
//header("Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept");
//header("Access-Control-Allow-Methods: GET, PATCH, PUT, POST, DELETE, OPTIONS");
echo json_encode($data);
//echo "Hello world!!\n";