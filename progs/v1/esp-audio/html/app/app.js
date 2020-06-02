var url = 'responder.php';
/* Модуль приложения */
var app = angular.module('app',[function(){
}])
.controller('mainCtrl',['$scope','dataFactory','$http',function($scope, dataFactory,$http){
    $scope.paused = false;
    $scope.request = function(params){
        $scope.success = false;
        $scope.error = false;
        $http.get("http://192.168.253.87/api?"+params).then(
            function(response){// success
                $scope.success = true;
            },
            function(response){// error
                $scope.error = response;
            }
        );

    };
    $scope.prevFolder = function(){
        $scope.request("action=prevfolder");
        $scope.paused = false;
    };
    $scope.prevTrack = function(){
        $scope.request("action=prev");
        $scope.paused = false;
    };
    $scope.nextTrack = function(){
        $scope.request("action=next");
        $scope.paused = false;
    };
    $scope.pause = function(){
        $scope.request("action=switchpause");
    };
    $scope.stop = function(){
        $scope.request("action=stop");
        $scope.paused = false;
    };
    $scope.play = function(){
        $scope.request("action=play");
        $scope.paused = false;
    };
    $scope.nextFolder = function(){
        $scope.request("action=nextfolder");
        $scope.paused = false;
    };



}])
.factory('dataFactory', function ($http) {
    return {
        lastRqTime:0,
//        deviceUrl:"http://artem-test.kb51.ru/api",
        deviceUrl:"http://192.168.253.80/api",

        loadProgress:function(state){
// Включает или гасит "колесо" загрузки
            if(state)
                $('#load-progress-icon').show();
            else
                $('#load-progress-icon').hide();
        },
        sendRq: function(params) {
            var date = new Date();
            this.lastRqTime = date.getTime();
//            this.loadProgress(true);
            var rqParams = params;
            return $http.get(this.deviceUrl,rqParams);
        },
        reloadPage: function(){
            this.loadProgress(true);
            location.reload();
        }
    };
});

