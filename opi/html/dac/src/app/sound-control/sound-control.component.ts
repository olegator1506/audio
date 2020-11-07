import { Component, OnInit, Inject } from '@angular/core';
import {MatDialog, MatDialogRef, MAT_DIALOG_DATA} from '@angular/material/dialog';
import { SoundControlConfig, SoundResponse } from '../model';
import { DacRqService } from '../dac-rq.service';
import {MatSlideToggleModule} from '@angular/material/slide-toggle';

@Component({
  selector: 'app-sound-control',
  templateUrl: './sound-control.component.html',
  styleUrls: ['./sound-control.component.css'],
  providers: [DacRqService]
})
export class SoundControlComponent implements OnInit {
  public config : SoundControlConfig;
  public mode:string = "eq";
  constructor(
    public dialogRef: MatDialogRef<SoundControlComponent>,
//    @Inject(MAT_DIALOG_DATA) public data: SoundControlConfig,
    private rqService : DacRqService
  ) { }

  ngOnInit(): void {
    this.rqService.request(`cmd=sound_control&op=state`)
    .subscribe((resp : SoundResponse) =>{
      this.config = resp.data;
    });
  }  
  eqPreset(mode : number): void {
    this.rqService.request(`cmd=sound_control&op=eq_preset&mode=${mode}`)
    .subscribe((resp : SoundResponse) =>{
      this.config = resp.data;
    });
  }  
  onEqChange(event,num) {
    var val = event.value;
    this.rqService.request(`cmd=sound_control&op=set_eq&band=${num}&value=${val}`)
    .subscribe((resp : SoundResponse) =>{
      this.config = resp.data;
    });
  }
  setGain(event, op) {
    var val = event.value;
    this.rqService.request(`cmd=sound_control&op=${op}&value=${val}`)
    .subscribe((resp : SoundResponse) =>{
      this.config = resp.data;
    });
  }

  toggleBass(){
    let v = this.config.bass ? 'off' : 'on';
    this.rqService.request(`cmd=sound_control&op=bass&state=${v}`)
    .subscribe((resp : SoundResponse) =>{
      this.config = resp.data;
    });
    
  }
  toggleDsp(){
    let v = this.config.dsp ? 'off' : 'on';
    this.rqService.request(`cmd=sound_control&op=dsp&state=${v}`)
    .subscribe((resp : SoundResponse) =>{
      this.config = resp.data;
    });

  }
  isEqAll(value:number) : boolean {
    var all : boolean = true;
    this.config.eq_values.forEach((element : number) => {
      if(element != value) all = false;
    });
    return all;
  }

}
