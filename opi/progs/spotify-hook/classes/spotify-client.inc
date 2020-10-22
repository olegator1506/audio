<?php
/**
 * Created by PhpStorm.
 * User: artem
 * Date: 21.10.20
 * Time: 10:11
 */

//require_once 'config.inc';
class TSpotifyClient
{
    protected $_cacheObj = NULL;
    protected $_curlError = NULL;
    protected $__authCode = NULL;
    protected $_config;
    function __construct($config)  {
        $this->_config = $config;
    }

    protected function _initCache(){
        if($this->_cacheObj) return true;
        $this->_cacheObj = new Memcached($this->_config['CACHE_PERSIST_ID']);
        if(!$this->_cacheObj->addServer($this->_config['MEMCACHE_HOST'],$this->_config['MEMCACHE_PORT'])) return false;
        return true;
    }

    protected function _setCache($id,$data,$expire){
        $this->_initCache();
        $this->_cacheObj->set($id,$data,time() + $expire);
    }
    protected function _getCache($id){
        $this->_initCache();
        return $this->_cacheObj->get($id);
    }
    public function queryServer($url,$params,$method='GET',$headers=NULL,$auth=NULL) {
        $ch = curl_init();
        curl_setopt($ch,CURLOPT_URL,$url);
        $fields = array();
        foreach($params as $k => $v)
            $fields[$k] = urlencode($v);
        $fields_string = '';
        foreach($fields as $key=>$value) {
            $fields_string .= $key.'='.$value.'&';
        }
        $fields_string = rtrim($fields_string, '&');
        $valid = true;
        switch ($method) {
            case 'POST':
                curl_setopt($ch,CURLOPT_POST,count($fields));
                curl_setopt($ch,CURLOPT_POSTFIELDS,$fields_string);
                break;
            case 'GET':
                if(count($params)) $url .= '?' . $fields_string;
                break;
            default:
                $valid = false;
                $this->_curlError = 'Invalid method $method';
                break;
        }
        if($valid) {
            if($auth)
                curl_setopt($ch, CURLOPT_USERPWD, $auth);
            curl_setopt($ch,CURLOPT_URL,$url);
            curl_setopt($ch,CURLOPT_HEADER,1);
            if(is_array($headers))
                curl_setopt($ch,CURLOPT_HTTPHEADER,$headers);
            curl_setopt($ch,CURLOPT_RETURNTRANSFER,1);
//        if($cookies)   curl_setopt($ch,CURLOPT_COOKIE,$cookies);
            $res = curl_exec($ch);
            if($res) {
                $result = curl_getinfo($ch);
                $h_size = $result['header_size'];
                $result['headers'] =  explode("\r\n",substr($res,0,$h_size));
                $result['body'] = substr($res,$h_size);
            }
            else {
                $this->_curlError = curl_error($ch);
                $result = false;
            }
        }
        curl_close($ch);
        return $result;
    }

    protected function _queryAuthCode(){
        $hdr = sprintf("Authorization: Basic %s",$this->_config['SPOTIFY_AUTH']);
        $result = $this->queryServer($this->_config['URL_AUTH_CODE'],['grant_type'=>'client_credentials'],'POST',[$hdr]);
        if(!$result) return false;
        if($result['http_code'] != 200) return false;
        if(!@$result['body']) return false;
        $data = json_decode($result['body'],true);
        if(!$data) return false;
        if(!@$data['expires_in']) return false;
        if(!@$data['access_token']) return false;
        return $data;
    }
     protected function _authCode(){
        if(@$this->__authCode) return $this->__authCode;
        $code = $this->_getCache('auth_code');
        if($code) {
            $this->__authCode = $code;
            return $this->__authCode;
        }
        $result = $this->_queryAuthCode();
        if(!$result)
            throw new Exception("Error fetching auth code from spotify server");
        $this->_setCache('auth_code',$result['access_token'],$result['expires_in']);
        $this->__authCode = $result['access_token'];
        return $this->__authCode;
     }
     protected function _queryTrackInfo($trackId){
        $result = $this->queryServer($this->_config['URL_TRACK_INFO'] . $trackId, [],'GET',["Authorization: Bearer ". $this->_authCode()]);
        if(!$result) return false;
        if(!$result['body']) return false;
        $data = json_decode($result['body'],true);
        return $data;
    }

    function getTrackInfo($trackId) {
        $cacheId = "track_info_by_id-{$trackId}";
        $result = $this->_getCache($cacheId);
        if($result) {
            $this->_cacheObj->touch($cacheId,$this->_config['TRACK_INFO_CACHE_TIMEOUT']);
            return $result;
        }
        $result = $this->_queryTrackInfo($trackId);
        if(!$result) return false;
        $this->_setCache($cacheId,$result,$this->_config['TRACK_INFO_CACHE_TIMEOUT']);
        return $result;
    }
}