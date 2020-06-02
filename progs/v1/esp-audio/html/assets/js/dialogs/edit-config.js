
angular.module('app')
.controller('configEditCtrl',['$scope','$uibModalInstance','dataFactory','$dialogs','config',function($scope, $uibModalInstance, dataFactory, $dialogs, config){
    $scope.cancell = function(){
        $uibModalInstance.close(false);
    };
    $scope.submit = function() {
        var fields =[];
        var vf = [];
        $scope.fields.forEach(function(field){
            fields.push(field.name);
            if(field.visible) vf.push(field.name);
        });
        $uibModalInstance.close({fields:fields,visible_fields:vf,page_rows:$scope.rpp});
    }
    $scope.isFieldVisible = function(fieldName) {
      return (config.session.visible_fields.indexOf(fieldName) != -1);

    };
    $scope.getField = function(fieldName) {
        var i;
        for(i=0;i < config.module.fields.length;i++) {
            if(config.module.fields[i].id == fieldName) return config.module.fields[i];
        }
        return false;
    };
    $scope.moveUp = function(num){
        var t;
        if(num == 0) {
            t = $scope.fields.shift();
            $scope.fields.push(t);
        } else {
            t = $scope.fields[num-1];
            $scope.fields[num-1] = $scope.fields[num];
            $scope.fields[num] = t;
        }
    };
    $scope.moveDown = function(num){
        var t;
        if(num == ($scope.fields.length -1)) {
            t = $scope.fields.pop();
            $scope.fields.unshift(t);
        } else {
            t = $scope.fields[num+1];
            $scope.fields[num+1] = $scope.fields[num];
            $scope.fields[num] = t;
        }
    }

    $scope.fields = [];
    config.session.fields.forEach(function(fieldName){
        var field = $scope.getField(fieldName);
        if(!field) return;
        $scope.fields.push({name:fieldName, title:field.header,visible:$scope.isFieldVisible(fieldName)});
    });
//    $scope.rowOpts = ['10','20','30','40','50','60','70','80','90','100'];
    $scope.rowOpts = [10,20,30,40,50,60,70,80,90,100];
    $scope.rpp = config.session.page_rows;

}]);