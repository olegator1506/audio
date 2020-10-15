import { Component } from '@angular/core';
import { DacRqService,WsService } from './dac-rq.service';
import { ChannelConfig, DacResponse, DacData } from './model';
import { MatButtonToggleChange } from '@angular/material/button-toggle';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'sample-ng-material';
  test = 'This is test';
  playPauseIcon = 'play_arrow';
  isPlaying = false;
  btnColor = "";
  dacConfig : DacData;
  source : any;
  selectedChannel:number;
  constructor(private dataSource : DacRqService, private ws:WsService){
  }
/*
  onChannelGroupChange(obj){
    var newChannel = obj.value;
    this.dataSource.selectChannel(newChannel)
    .subscribe((resp : DacResponse) => {
      this.dacConfig = resp.data;
      this.selectedChannel = resp.data.selected_channel_num;
    });
  }
*/  
  onClickChannel(num:number) {
    this.dataSource.selectChannel(num)
    .subscribe((resp : DacResponse) => {
      this.dacConfig = resp.data;
    });
  }
  isChannelSelected(chNum:number) {
    return (chNum == this.dacConfig.selected_channel_num);
  }
  play(){
    this.isPlaying = true;
    this.playPauseIcon = 'pause';
  }
  pause(){
    this.isPlaying = false;
    this.playPauseIcon = 'play_arrow';
  }
  onPlayClick(){
    if(this.isPlaying) this.pause();
    else this.play();
  };
  ngOnInit() {
    this.dataSource.getConfig()
    .subscribe((resp : DacResponse) => {
      this.dacConfig = resp.data;
    });
  }
  errorHandler(){

  }
  onEqChange($event,num) {
    var val = $event.value;
    this.dataSource.setEq(num,val)
    .subscribe((resp : DacResponse) =>{
      this.dacConfig = resp.data;
    });
  }
  testFunc(){
    this.dataSource.getConfig()
    .subscribe((resp : DacResponse) => {
      this.dacConfig = resp.data;
    });
  }

}
class Test extends AppComponent {

}
