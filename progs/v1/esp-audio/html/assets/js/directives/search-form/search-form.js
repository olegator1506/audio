app.controller('searchFormCtrl',['$scope','$rootScope','$uibModal','dataFactory',function($scope, $rootScope, $uibModal, dataFactory){
    $scope.loadProgress = false;
    $scope.$on("configLoaded", function(event,data){
        $scope.filterField  = (data.session.filter_field == undefined) ? "all" : data.session.filter_field;
        $scope.filterOpp = (data.session.opp == undefined) ? data.config.default_http_values.opp : data.session.opp;
        $scope.filter_value  = (data.session.filter_value == undefined) ? "" : data.session.filter_value;
        $scope.filterFieldOpts = [];
        data.module.fields.forEach(function(field){
            $scope.filterFieldOpts.push({id:field.id,title:field.header});
        });
        if(data.session.filter == undefined) {
            $scope.advancedFilter = [];
            $scope.filterFieldOpts.forEach(function (field) {
                if(field.id =='all') return;
                $scope.advancedFilter.push({id:field.id,title:field.title,value:'',op:'like'});
            });
        } else $scope.advancedFilter = data.session.filter;
        $scope.config = data;
        $scope.mode = 'simple';
    });

    $scope.onChange = function(){
        var val = $('#search_form_value').val();
        var field = $('#search_form_field').val();
        var opp = $('#search_form_opp').val();
        $scope.loadProgress = true;
        $rootScope.$broadcast("search_opt_changed",{mode:$scope.mode,filter_field:field,filter_value:val,opp:opp});
    };

    $scope.openAdvanced = function(){
        var data = {config:$scope.config, fields:$scope.advancedFilter};
        var dlgParams = {
            size:'md',
            backdrop:'static',
            templateUrl: 'templates/dialogs/advanced-search.html',
            controller: 'advaancedSearchCtrl',
            windowClass: 'modalbackground',
            resolve: {
                data: function () {
                    return angular.copy(data);
                }

            }
        };
        var dlg = $uibModal.open(dlgParams);
        dlg.result.then(function (res) {
            if(res) $scope.advancedFilter = res;

        });

    };


    $scope.$on('data_table_updated',function(event){
        $scope.loadProgress = false;
    });
}]);

app.controller('advaancedSearchCtrl',['$scope','$rootScope','$uibModalInstance','dataFactory','data',function($scope, $rootScope, $uibModalInstance, dataFactory, data){
    $scope.fields = data.fields;
    $scope.config = data.config;
    $scope.cancell = function(){
        $uibModalInstance.close(false);
    };

    $scope.submit = function(){
        $rootScope.$broadcast("search_advanced",$scope.fields);

    };
    $scope.$on('data_table_updated',function(event){
        $uibModalInstance.close($scope.fields);
    });


}]);