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
import {MatListModule} from '@angular/material/list';
import { SoundControlComponent } from './sound-control/sound-control.component';
import {MatDialogModule} from '@angular/material/dialog';
import {MatSlideToggleModule} from '@angular/material/slide-toggle';
@NgModule({
  declarations: [
    AppComponent,
    TrackInfoComponent,
    PlayListComponent,
    SoundControlComponent
  ],
  imports: [
    MatSliderModule,
    MatIconModule,
    MatButtonModule,
    MatCardModule,
    MatCheckboxModule,
    MatSelectModule,
    MatListModule,
    BrowserModule,
    BrowserAnimationsModule,
    MatButtonToggleModule,
    MatSlideToggleModule,
    HttpClientModule,
    MatDialogModule
  ],
  providers: [
    DacRqService,
    WebSocketService
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
