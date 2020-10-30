import { ComponentFixture, TestBed } from '@angular/core/testing';

import { SoundControlComponent } from './sound-control.component';

describe('SoundControlComponent', () => {
  let component: SoundControlComponent;
  let fixture: ComponentFixture<SoundControlComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ SoundControlComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(SoundControlComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
