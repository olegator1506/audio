import { Injectable } from '@angular/core';
import { HttpClient } from "@angular/common/http";
import { ChannelConfig } from './model'
import { Observable } from 'rxjs';



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
    this._baseUrl = "http://localhost:8000/";
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
}
