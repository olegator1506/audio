import { Component } from '@angular/core';

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
}
class Test extends AppComponent {

}
