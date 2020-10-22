import { Injectable } from '@angular/core';
import { Observable } from "rxjs";

@Injectable()
export class WebSocketService {
  private ws : WebSocket;
  constructor() { }
  public createSocket(url : string) {
    this.ws = new WebSocket(url);
    return new Observable(
      observer => {
        this.ws.onmessage = (event) => observer.next(event.data);
        this.ws.onerror = (event) => observer.error(event);
        this.ws.onclose = (event) => observer.complete();
      }
    );
    }
  public sendMessage(message : any){
    this.ws.send(message);
  }
} 



