import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { HttpClientModule } from "@angular/common/http"

import { AppComponent } from './app.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';

import { MatSliderModule } from '@angular/material/slider';
import { MatButtonModule } from '@angular/material/button';
import {MatIconModule} from '@angular/material/icon';
import {MatButtonToggleModule} from '@angular/material/button-toggle';
import { MatCheckboxModule } from '@angular/material/checkbox';

import { DacRqService } from './dac-rq.service';
import { WebSocketService } from './web-socket.service';
import { TrackInfoComponent } from './track-info/track-info.component';
import { MatCardModule } from '@angular/material/card';
import { PlayListComponent } from './play-list/play-list.component';
import { MatSelectModule } from '@angular/material/select';
@NgModule({
  declarations: [
    AppComponent,
    TrackInfoComponent,
    PlayListComponent
  ],
  imports: [
    MatSliderModule,
    MatIconModule,
    MatButtonModule,
    MatCardModule,
    MatCheckboxModule,
    MatSelectModule,
    BrowserModule,
    BrowserAnimationsModule,
    MatButtonToggleModule,
    HttpClientModule
  ],
  providers: [
    DacRqService,
    WebSocketService
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
