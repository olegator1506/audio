import { Injectable } from '@angular/core';
import { HttpClient } from "@angular/common/http";
import { ChannelConfig } from './model'
import { Observable } from 'rxjs';

@Injectable()
export class DacRqService {
  private _channels : ChannelConfig[] = [
    new ChannelConfig(0,"AUX1",'AUX',1,false),
    new ChannelConfig(1,"AUX2",'AUX',2,false),
    new ChannelConfig(2,"LINE",'LINEIN',0,false),
    new ChannelConfig(2,"ALSA",'ALSA',0,true)
  ];
  constructor(private http: HttpClient) { }
  getChannels() : ChannelConfig[]{
    return this._channels;
  }  
  getConfig()  {
    return this.http.get("http://192.168.253.10:8000/?cmd=get_state");
  }
}
