app.controller('formEditRecordCtrl',['$scope','$uibModalInstance','dataFactory','$dialogs','data',function($scope, $uibModalInstance, dataFactory, $dialogs, data){
    $scope.init = function() {
        $scope.dataLoaded = false;
        $scope.formTitle = data.title + ":" + (data.recordId ? "редактирование записи":"добавление записи");
        dataFactory.sendRq({ object:data.moduleName, action:'get_record',id:data.recordId,form_action:$scope.addMode ? 'add' : 'edit'})
            .then(function(response){
                dataFactory.loadProgress(false);
                $scope.edit_data = response.data;
                $scope.dataLoaded = true;
                $scope.fields.forEach(function(field,num){
                    if(field.mandatory) $scope.fields[num].style = "font-weight: bold;";
                    if(field.type === undefined) $scope.fields[num].type = 'string';
                    $scope.fields[num].value = $scope.edit_data[field.id];
                    if((field.type == 'cb') || (field.type == 'checkbox')) {
                        if(field.true_value == undefined) field.true_value = '1';
                        if(field.false_value == undefined) field.false_value = '0';
                    }
                });
            });
    };
    $scope.cancell = function(){
        $uibModalInstance.close(false);
    };
    $scope.formSubmit = function(){
        var editData = {};
        $scope.fields.forEach(function(field){
            editData[field.id] = field.value;
        });
        var rqData = {object:data.config.module.name,action:'apply_form',edit_data:editData,add_mode:$scope.addMode};
        if(!$scope.addMode)
            rqData.id = $scope.recordId;
        $('#loadingdiv').show();
        dataFactory.sendRq(rqData)
            .then(
                function(response){
                    dataFactory.loadProgress(false);
                    if(response.data.op_result == 'error')
                        $scope.formErrors = response.data.form_errors;
                    else {
                        $uibModalInstance.close(true);
                    }
                },
                function(error){
                    dataFactory.loadProgress(false);
                    $scope.formErrors.push(error.data.message);
                }
            );
        return false;
    };

    $scope.isEditable = function(field) {
      if(field.id == 'all') return false;
      if(field.type == 'no_edit') return false;
      if($scope.addMode && field.skip_on_add) return false;
      return true;
    };
    $scope.addMode = (data.recordId === false);
    $scope.recordId = data.recordId;
    $scope.fields = data.config.module.fields;
    $scope.formErrors =[];
    $scope.init();
}]);

