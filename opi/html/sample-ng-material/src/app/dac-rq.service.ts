import { Injectable } from '@angular/core';
import { HttpClient } from "@angular/common/http";
import { ChannelConfig } from './model'
import { Observable } from 'rxjs';
import { catchError, tap, switchAll } from 'rxjs/operators';
import { webSocket, WebSocketSubject } from "rxjs/webSocket";
import { EMPTY, Subject } from 'rxjs';
export const WS_ENDPOINT = `ws://{$location.host}`;
@Injectable()
export class DacRqService {
  private _baseUrl : string;
  private _channels : ChannelConfig[] = [
    new ChannelConfig(0,"AUX1",'AUX',1,false),
    new ChannelConfig(1,"AUX2",'AUX',2,false),
    new ChannelConfig(2,"LINE",'LINEIN',0,false),
    new ChannelConfig(2,"ALSA",'ALSA',0,true)
  ];
  private socket$: WebSocketSubject<any>;
  constructor(private http: HttpClient) { 
    var l = location;
    this._baseUrl = `${location.protocol}//${location.hostname}:8000`;
    this.
  }
  getWebSocket() {

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

export class WsService {
  private socket$: WebSocketSubject<any>;
  private messagesSubject$ = new Subject();
  public messages$ = this.messagesSubject$.pipe(switchAll(), catchError(e => { throw e }));
 
  public connect(): void {
     if (!this.socket$ || this.socket$.closed) {
      this.socket$ = this.getNewWebSocket();
      const messages = this.socket$.pipe(
        tap({
          error: error => console.log(error),
        }), catchError(_ => EMPTY));
      this.messagesSubject$.next(messages);
    }
  }
 
  private getNewWebSocket() {
    return webSocket(WS_ENDPOINT);
  }
  sendMessage(msg: any) {
    this.socket$.next(msg);
  }
  close() {
    this.socket$.complete(); 
  }
}
