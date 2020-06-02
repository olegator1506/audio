app.controller('formEditHostCtrl',['$scope','$uibModalInstance','dataFactory','$dialogs','hostId',function($scope, $uibModalInstance, dataFactory, $dialogs, hostId){
    $scope.changeRegister = function() {
        if($scope.edit_data.register == '0') $scope.unregister();
        if($scope.edit_data.register == '1') $scope.register();
    };
    $scope.changeClass = function() {
        if(($scope.classTemp == 8) || ($scope.classTemp == 9)) {
            var num = 8;
            num = num.toString();
            $scope.edit_data.cms = $scope.edit_data.csa = num;
        }
        if($scope.classTemp == '4') {
            $scope.classTemp = $scope.edit_data.class;
            $scope.unregister();
        }
        else {
            if($scope.edit_data.class == '4')
                $scope.register();
            $scope.edit_data.class = $scope.classTemp;
        }
    };
    $scope.unregister = function() {
        if($scope.addMode) { // При добавлении узла только меняем значения соответствующих полей
            $scope.updateRegInfo();
            $scope.edit_data.register = '0';
            $scope.edit_data.class = '4';
            $scope.classTemp = '4';
            if($scope.edit_data.ip.length >0)
                $scope.regIp = $scope.edit_data.ip;
            $scope.selectNetwork();
            $scope.edit_data.name = 'unreg-'+$scope.edit_data.mac;
            $scope.edit_data.cms = '0';
            $scope.edit_data.csa = '0';
            $scope.flags.forEach(function(el,index, arr){
                $scope.flags[index].value = 0;
            });
            $scope.flag_set = 0;
            return;
        }
        $dialogs.confirm('Вы действительно хотите отменить регистрацию данного узла (Все внесенные изменения будут потеряны)?',function(){
            dataFactory.sendRq({object:'hosts',action:'unreg',id:$scope.hostId})
                .then(function(response){
                    dataFactory.loadProgress(false);
                    if(!response.op_result)
                        $scope.formErrors = response.errors;
                    $scope.init();
                })
        });
    };
    $scope.register = function() {
        $scope.edit_data.register = '1';
        if($scope.regIp)
            $scope.edit_data.ip = $scope.regIp;
        else
            $scope.selectNetwork();
        if($scope.regInfo) {
//            var fields = ['name','class','inet_public','cms','csa'];
// Restore regInfo
            if($scope.regInfo.class != '4') $scope.edit_data.class = $scope.regInfo.class;
            if($scope.regInfo.name.substring(0,6) != 'unreg-') $scope.edit_data.name = $scope.regInfo.name;
            $scope.edit_data.inet_public = $scope.regInfo.inet_public;
//            $scope.edit_data.cms = $scope.regInfo.cms;
//            $scope.edit_data.csa = $scope.regInfo.csa;
//            $scope.updateFlags();
        }
    };
    $scope.selectNetwork = function() {
        var id = $scope.network;
        var range =  ($scope.edit_data.register == '1') ? 'reg':'unreg';
        dataFactory.sendRq({object:'hosts',action:'get_free_ip',range:range,net:id})
            .then(function(response){
                dataFactory.loadProgress(false);
                var v = response.data.trim();
                if(v.length >0) {
                    $scope.edit_data.ip = v;
                    if(!$scope.$$phase)
                        $scope.$apply(function(){$scope.edit_data.ip});
                }
            });
    };
    $scope.updateRegInfo = function() {
        var fields = ['name','class','cms','csa'];
        $scope.regInfo = {};
        fields.forEach(function(f){
            $scope.regInfo[f] = $scope.edit_data[f];
        });
    };
    $scope.changeFlags = function(){
        var fl = 0;
        $scope.flags.forEach(function(el,index, arr){
            if(el.name == 'admin_grant') {

            }
            if(el.value)
                fl +=  el.mask;
        });
        $scope.edit_data.flag_set = fl;
    };
    $scope.formSubmit = function(){
        $scope.edit_data.tn = $scope.tn;
        var rqData = {object:'hosts',action:'apply_form',edit_data:$scope.edit_data,add_mode:$scope.addMode};
        if(!$scope.addMode)
            rqData.id = $scope.hostId;
        dataFactory.sendRq(rqData)
            .then(function(response){
                dataFactory.loadProgress(false);
                if(!response.data.op_result)
                    $scope.formErrors = response.data.errors;
                else {
                    $uibModalInstance.close(true);
                }
            });
        return false;
    };
    $scope.init = function() {
        $scope.dataLoaded = false;
        $scope.formTitle = "Редактирование хоста";
        $scope.regBtnDisabled = true;
        $scope.flags = [
            {name:'inet_public',title: 'Интернет-киоск',mask:16,value:0},
            {name:'server',title: 'Сервер',mask:1,value:0},
            {name:'nobrowseable',title: 'Не показывать в обозревателе',mask:8,value:0},
            {name:'admin_grant',title: 'Назначены права администратора',mask:32,value:0},
            {name:'inet_access',title: 'Доступ в интернет',mask:64,value:0},
            {name:'ad_member',title: 'Включен в домен',mask:128,value:0},
	        {name:'dlp',title: 'DLP агент',mask:2048,value:0},
            {name:'auto_auth',title: 'Автоматическая (прозрачная) авторизация',mask:4096,value:0}
        ];
        dataFactory.sendRq({object:'hosts',action:'get_host',id:$scope.hostId,form_action:$scope.addMode ? 'add' : 'edit'})
            .then(function(response){
                dataFactory.loadProgress(false);
                $scope.networks = response.data.networks;
                $scope.clientNet = response.data.client_network;
                $scope.edit_data = response.data.edit_data;
                $scope.tn = response.data.edit_data.tn;
                $scope.selectOptions = response.data.options;
                $scope.dataLoaded = true;
                $scope.network = $scope.clientNet.id;
                $scope.regInfo = false;
                if($scope.edit_data.register == '1') $scope.updateRegInfo();
                $scope.flags.forEach(function(el,index, arr){
                    $scope.flags[index].value = (($scope.edit_data.flag_set & el.mask) > 0) ? 1:0;
//            $('#form-field-class').val($scope.edit_data.class);
                    $scope.classTemp = $scope.edit_data.class;
                });
            });
    };
    $scope.cancell = function(){
        $uibModalInstance.close(false);
    };
    $scope.addMode = (hostId === false);
    $scope.hostId = hostId;
    $scope.formErrors =[];
    $scope.init();
}]);

