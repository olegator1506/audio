import { Component } from '@angular/core';
import { DacRqService } from './dac-rq.service';
import { WebSocketService } from './web-socket.service';
import { ChannelConfig, DacResponse, DacData, PlayerResponse } from './model';
import { MatButtonToggleChange } from '@angular/material/button-toggle';
import { TrackInfo, PlayerStatus } from "./model";
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
  track : TrackInfo;
  selectedPlayList:string = "";
  playerStatus : PlayerStatus;
  constructor(private dataSource : DacRqService, private wsService: WebSocketService){
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
      if(this.isFileChannel()) 
        this.playerRq("status","");
    });
  }
  isChannelSelected(chNum:number) {
    return (chNum == this.dacConfig.selected_channel_num);
  }
  isFileChannel() : boolean {
    return (this.dacConfig.channels[this.dacConfig.selected_channel_num].type == 'file');
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
      if(this.isFileChannel())
        this.playerRq("status","");

    });
    this.wsService.createSocket( `ws://${location.hostname}:8000`)
    .subscribe(
      ( data : string ) => {
        let info = JSON.parse(data);
        switch(info.cmd){
          case 'pub_spotify_stop':
          case 'pub_spotify_start':
          case 'pub_spotify_change': 
            this.track = info;
            break;
        }
      },
      (err : string) =>{
        console.log(err)
      },
      () => {
        console.log( 'The observable stream is complete')
      }  
    );
/*
    setInterval(() => {
      if(this.isFileChannel())
        this.playerRq("status","");
    }, 2000);  
*/
  }

  errorHandler(message : string){

  }
  onEqChange($event,num) {
    var val = $event.value;
    this.dataSource.setEq(num,val)
    .subscribe((resp : DacResponse) =>{
      this.dacConfig = resp.data;
    });
  }
  setBass(state){
    this.dataSource.setBass(state)
    .subscribe((resp : DacResponse) =>{
      this.dacConfig.bass = state;
    });

  }
  testFunc(){
    this.dataSource.getConfig()
    .subscribe((resp : DacResponse) => {
      this.dacConfig = resp.data;
    });
  }
  onSelectPlayList($event) {
    let value = $event.value;
    this.selectedPlayList = $event.value;
  }
  /*
  loadPlayList(){
    this.dataSource.loadPlayList(this.selectedPlayList)
      .subscribe((resp : PlayerResponse) => {
          this.playerTracks = resp.data.tracks;
      });

  }
  */
  playerRq(op:string,arg:string | ""){
    this.dataSource.playerRq(op,arg)
      .subscribe((resp : PlayerResponse) => {
          this.playerStatus = resp.data;
      });
  }
  playerButtonDisabled(button : string) : boolean {

    if(!this.playerStatus.tracks) return true; // список пустой - все кнопки заблокированы
    switch(button) {
      case 'prev':
        if(this.playerStatus.track_num < 2) return true;
      case 'pause':
        if(this.playerStatus.is_playing) return false;
        return true;
      case "play":
        return false;
      case 'next':
        if(this.playerStatus.track_num == this.playerStatus.tracks.length) return true;
        return false;
    }

    return false;
  }
  playerButtonClick(button : string) {
    switch(button) {
      case 'prev':
        this.playerRq('prev','');
        return;
      case 'pause':
        if(!this.playerStatus.is_playing) return;
        if(this.playerStatus.is_paused) 
          this.playerRq('resume','');  
         else 
          this.playerRq('pause','');  
        return;
      case 'play':
        if(this.playerStatus.is_playing) 
          this.playerRq('stop','');  
         else 
          this.playerRq('play','');  
        return;
      case 'next':
        this.playerRq('next','');
        return;
    }
  }
}
class Test extends AppComponent {}
