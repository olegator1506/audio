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

export class DacData {
  constructor(
    public channels?:ChannelConfig[]
  ){}  

}

export class DacResponse {
  constructor(
    public result?:string,
    public data?:DacData
  ){}  
}

