import { Component } from '@angular/core';
import { DacRqService } from './dac-rq.service';
import { ChannelConfig, DacResponse } from './model';
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
  channels : ChannelConfig[];
  selectedChannelNum: number;
  source : any;
  constructor(private dataSource : DacRqService){
    this.selectedChannelNum = 1;
  }

  onChannelButtonClick(obj : MatButtonToggleChange){
    this.selectedChannelNum = obj.value;
  }
  isChannelSelected(chNum:number) {
    return (chNum == this.selectedChannelNum);
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
/*
    this.dataSource.getConfig()
    .subscribe((resp : ChannelConfig[]) => {
      this.channels = resp.channels;
    });
*/    
  }
  testFunc(){
    this.dataSource.getConfig()
    .subscribe((resp : DacResponse) => {
      this.channels = resp.data.channels;
    });
  }

}
class Test extends AppComponent {

}
