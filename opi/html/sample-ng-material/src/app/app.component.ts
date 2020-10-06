import { Component } from '@angular/core';
import { DacRqService } from './dac-rq.service';
import { ChannelConfig } from './model';

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
  constructor(){
    this.dataSource = new DacRqService();
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
