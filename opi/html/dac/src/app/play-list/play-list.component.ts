import { Component, OnInit, Input } from '@angular/core';


@Component({
  selector: 'app-play-list',
  templateUrl: './play-list.component.html',
  styleUrls: ['./play-list.component.css']
})
export class PlayListComponent implements OnInit {
  @Input("model")
  listNames : string[];
  public selectedItem : string = "";
  constructor() { }

  ngOnInit(): void {
  }
  onSelectName($event){
    
  }

}
