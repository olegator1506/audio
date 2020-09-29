<?php
/**
 * Created by PhpStorm.
 * User: artem
 * Date: 28.09.20
 * Time: 21:48
 */
class Player {
    protected $_cmdOutput, $_cmdRetVal,$_conf, $_processPipes, $_process, $__isRunning;
    public function __construct(){
        global $config;
        $this->_conf = $config['player'];
        $this->_process = NULL;
    }
    protected function _rq($params){
        $this->_cmdOutput = [];
        $this->_cmdRetVal = 0;
        $cmd = "{$this->_conf['command']} --session-name {$this->_conf['session_name']} {$params}";
        echo "{$cmd}\n";
        exec($cmd, $this->_cmdOutput, $this->_cmdRetVal);
    }
    protected function _startDaemon(){
        $cmd = "{$this->_conf['command']} --session-name {$this->_conf['session_name']} --device {$this->_conf['output_device']} -i daemon --quiet&\n";
//        exec($cmd, $this->_cmdOutput, $this->_cmdRetVal);
        $descriptorspec = [
            0 => array("pipe", "r"),  // stdin - канал, из которого дочерний процесс будет читать
            1 => array("pipe", "w"),  // stdout - канал, в который дочерний процесс будет записывать
            2 => array("file", "/tmp/alsa-player-output.txt", "a") // stderr - файл для записи
        ];
        $cwd = '/tmp';

        $this->_process = proc_open($cmd,$descriptorspec, $this->_processPipes,$cwd);
    }
    protected function _getStatus(){
        $this->_rq('--status');
        if($this->_cmdRetVal != 0) return false;
        $status = [];
        foreach($this->_cmdOutput as $line) {
            if (!strstr($line, ':')) continue;
            list($key, $val) = explode(':',$line,2);
            $status[trim($key)] = trim($val);
        }
        return $status;
    }
    protected function _isRunning(){
        if(is_null($this->__isRunning)) {
            $this->_rq('--status');
            $this->__isRunning = ($this->_cmdRetVal == 0);
        }
        return $this->__isRunning;
    }

    /**
     * @description Загружает программу alsaplayer
     */
    public function load(){
        if(!$this->_isRunning())
            $this->_startDaemon();
    }

    public function quit(){
        $this->_rq('--quit');
    }
    public function status(){
        $status = $this->_getStatus();
        if(!$status) return;
        foreach($status as $key => $val)
            echo "{$key} = $val\n";
    }
    public function addFile($fileName){
        if(substr($fileName,0,1) != '/'){
            $cwd = getcwd();
            $fileName = "{$cwd}/{$fileName}";
        }
        $this->_rq("--enqueue ". escapeshellarg($fileName));
    }
    public function start(){
        $this->_rq('--start');
    }
    public function next(){
        $this->_rq('--next');
    }

}