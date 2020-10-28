import { Injectable } from '@angular/core';
import { HttpClient } from "@angular/common/http";
import { ChannelConfig } from './model'
import { Observable } from 'rxjs';
import { catchError, tap, switchAll } from 'rxjs/operators';

@Injectable()
export class DacRqService {
  private _baseUrl : string;
  private _channels : ChannelConfig[] = [
    new ChannelConfig(0,"AUX1",'AUX',1,false),
    new ChannelConfig(1,"AUX2",'AUX',2,false),
    new ChannelConfig(2,"LINE",'LINEIN',0,false),
    new ChannelConfig(2,"ALSA",'ALSA',0,true)
  ];
  constructor(private http: HttpClient) { 
    var l = location;
    this._baseUrl = `${location.protocol}//${location.hostname}:8000`;
  }
  getChannels() : ChannelConfig[]{
    return this._channels;
  }  
  getConfig()  {
    return this.http.get(`${this._baseUrl}?cmd=get_state`);
  }
  setEq(num:number,val:number)  {
    return this.http.get(`${this._baseUrl}?cmd=eq&band=${num}&value=${val}`);
  }
  selectChannel(num:number) {
    return this.http.get(this._baseUrl +"?cmd=ch_sel_num&num="+num);
  }
  setBass(state:boolean){
    var stateStr = state ? 'on':'off';
    var url = this._baseUrl +"?cmd=bass&state="+stateStr;
    return this.http.get(url);
  }
  playerRq(op:string,arg:string|"") {
    var url = `${this._baseUrl}?cmd=player&op=${op}&arg=${arg}`;
    return this.http.get(url);
  }
}
