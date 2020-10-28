import { TestBed } from '@angular/core/testing';

import { DacRqService } from './dac-rq.service';

describe('DacRqService', () => {
  let service: DacRqService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(DacRqService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});

