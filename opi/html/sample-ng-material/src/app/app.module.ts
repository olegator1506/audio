import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { HttpClientModule } from "@angular/common/http"

import { AppComponent } from './app.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';

import { MatSliderModule } from '@angular/material/slider';
import { MatButtonModule } from '@angular/material/button';
import {MatIconModule} from '@angular/material/icon';
import {MatButtonToggleModule} from '@angular/material/button-toggle';

import { DacRqService } from './dac-rq.service';

@NgModule({
  declarations: [
    AppComponent
  ],
  imports: [
    MatSliderModule,
    MatIconModule,
    MatButtonModule,
    BrowserModule,
    BrowserAnimationsModule,
    MatButtonToggleModule,
    HttpClientModule
  ],
  providers: [
    DacRqService
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
