import { Component } from '@angular/core';
import { DacRqService } from './dac-rq.service';
import { ChannelConfig } from './model';
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
  dataSource : DacRqService;
  channels : ChannelConfig[];
  selectedChannelNum: number;
  source : any;
  constructor(){
    this.dataSource = new DacRqService();
    this.selectedChannelNum = 1;
  }

  onChannelButtonClick(obj : MatButtonToggleChange){
    this.selecteChannelNum(obj.value);
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
    this.channels = this.dataSource.getChannels();
  }
}
class Test extends AppComponent {

}
