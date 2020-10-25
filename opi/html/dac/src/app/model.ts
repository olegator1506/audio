import { Observable } from 'rxjs';

// Классы моделей 
export class ChannelConfig {
  constructor(
    public num?:number,
    public name?:string,
    public type?:string,
    public auxNum?:number,
    public support_tracks?:boolean
    
  ){}  
}

export class EqState {
  constructor(
    public band_count?:number,
    public max_value?:number,
    public min_value?:number,
    public labels?:string[],
    public values?:number[]
  ){}  
}

export class DacData {
  constructor(
    public channels?:ChannelConfig[],
    public eq?:EqState,
    public selected_channel_num?:number,
    public bass? : boolean,
    public play_lists?: string[]
  ){}  

}

export class TrackInfo {
  constructor(
    public trackId? : string,
    public album? : string,
    public artist? : string,
    public track_name? :string,
    public image? :string,
    public duration_string? : string,
    public duration? : number
  ){}  
}

export class DacResponse {
  constructor(
    public result?:string,
    public data?:DacData
  ){}  
}
