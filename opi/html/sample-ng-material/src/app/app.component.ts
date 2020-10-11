import { Component } from '@angular/core';
import { DacRqService } from './dac-rq.service';
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
  constructor(private dataSource : DacRqService){
  }

  onChannelButtonClick(obj : MatButtonToggleChange){
//    this.selectedChannelNum = obj.value;
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
  testFunc(){
    this.dataSource.getConfig()
    .subscribe((resp : DacResponse) => {
      this.dacConfig = resp.data;
    });
  }

}
class Test extends AppComponent {

}
