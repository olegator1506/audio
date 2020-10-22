import { Component, OnInit, Input } from '@angular/core';
import { TrackInfo } from "../model";
@Component({
  selector: 'app-track-info',
  templateUrl: './track-info.component.html',
  styleUrls: ['./track-info.component.css']
})
export class TrackInfoComponent implements OnInit {
  @Input("model")
  trackInfoData : TrackInfo;
  constructor() { }

  ngOnInit(): void {
  }

}
