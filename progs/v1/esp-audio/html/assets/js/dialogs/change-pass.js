app.controller('dlgChangePassCtrl',['$scope', '$uibModalInstance','dataFactory','$dialogs','data',function($scope, $uibModalInstance,dataFactory, $dialogs, data){
    $scope.checkValid = function(){
        var p1 = $scope.pass1.trim();
        var p2 = $scope.pass2.trim();
        if(p1 != p2) return false;
        if(p1.length == 0) return false;
        return true;
    };
    $scope.no = function(){
        $uibModalInstance.close();
    };
    $scope.yes = function(){
        var p = $scope.pass1.trim();
        dataFactory.sendRq({object:data.module, id:data.rowId, password:p,action:'change_password'}).then(
            function(response){
		dataFactory.loadProgress(false);
                $uibModalInstance.close();
            },function(error){
		dataFactory.loadProgress(false);
                $scope.error = error.data.message;
            }
        );
    };
    $scope.pass1 = '';
    $scope.pass2 = '';
    $scope.error = '';
    $scope.title = data.title;
}]);