/**
 * Created by artem on 01.11.16.
 */
app.directive('selectParent',['dataFactory',function(dataFactory){
    return {
        restrict: 'E',
        templateUrl:'assets/js//directives/select-parent/select-parent.html' ,
        link: function($scope,element,attrs,controller) {},
        scope:{
            value:'=',
            event:'@',
            fieldName:'@',
            fields:'@',
            table:'@',
            idField:'@'
        },
//        scope:true,
        controller:    function($scope,dataFactory) {
            $scope.startEdit = function() {
                $scope.editMode = true;
                $scope.mask = $scope.value;
                $scope.variants = [{id:$scope.value, descr:$scope.title}];
            };
            $scope.changeMask = function(){
                var mask = $scope.mask;
                $scope.variants = [];
                if(mask.length < 3) {
                    $scope.variants = [];
                    return;
                };
                dataFactory.searchParent(_moduleName,$scope.table,mask,$scope.fields)
                    .then(function(response){
                        dataFactory.loadProgress(false);
                        $scope.variants = response.data;
//      $scope.$apply();
                    });
            };
            $scope.selectVariant = function(variant){
                $scope.value = variant.id;
                $scope.title = variant.descr;
                var id = '#parent-field-'+$scope.fieldName;
                $(id).val($scope.value);
                $scope.editMode = false;
            };
// Init
            $scope.dataFactory = dataFactory;
            $scope.$watch('value',function(newVal,oldVal,scope){
                if((typeof oldVal == 'undefined') && (typeof newVal != 'undefined')) {
                    dataFactory.getRecords(_moduleName,$scope.table,$scope.idField + '="'+$scope.value+'"' ,"LIMIT 1")
                        .then(function(response){
                            dataFactory.loadProgress(false);
                            if(response.data.length == 1) {
                                var fields = $scope.fields.split(',');
                                var els = [];
                                for(var n = 0; n < fields.length; n++) {
                                    els.push(response.data[0][fields[n]]);
                                }
                                $scope.title = els.join(' ');
                            }
                        });
                }
            });

            $scope.title = $scope.value;
            $scope.editMode = false;


        }

    }

}]);