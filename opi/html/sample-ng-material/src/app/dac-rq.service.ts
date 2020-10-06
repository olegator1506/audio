import { Injectable } from '@angular/core';
import { ChannelConfig } from './model'
import { Observable, of } from 'rxjs';
//import { Observable } from "rxjs/Observable";
//import "rxjs/add/observable/from";

@Injectable({
  providedIn: 'root'
})
export class DacRqService {
  private _channels : ChannelConfig[] = [
    new ChannelConfig(0,"AUX1",'AUX',1,false),
    new ChannelConfig(1,"AUX2",'AUX',2,false),
    new ChannelConfig(2,"LINE",'LINEIN',0,false),
    new ChannelConfig(2,"ALSA",'ALSA',0,true)
  ];
  constructor() { }
  getChannels(): ChannelConfig[] {
//    return Observable.from(this._channels);
    return this._channels;
  }
}
