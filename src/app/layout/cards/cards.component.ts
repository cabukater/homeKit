import { IotDataService } from './../../services/iot-data.service';
import { Component, OnInit } from '@angular/core';
import { snapshotChanges } from '@angular/fire/compat/database';

@Component({
  selector: 'app-cards',
  templateUrl: './cards.component.html',
  styleUrls: ['./cards.component.scss']
})
export class CardsComponent implements OnInit {
  testes : any = [];

  constructor(
    private IotDataService: IotDataService
  ) { }

  ngOnInit(): void {
    this.IotDataService.getAll().snapshotChanges().pipe()
      .subscribe((data) => (
       this.testes = data
     )
    )

  }

}
