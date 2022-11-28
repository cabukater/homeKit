import { IotDataService } from './../../services/iot-data.service';
import { Component, OnInit } from '@angular/core';
import { map } from 'rxjs/operators';

@Component({
  selector: 'app-cards',
  templateUrl: './cards.component.html',
  styleUrls: ['./cards.component.scss']
})
export class CardsComponent implements OnInit {
  
  devices: any;
  currentTutorial = null;
  currentIndex = -1;
  umidade : number | undefined;
  public now: Date = new Date();

  constructor(
    private IotDataService: IotDataService
  ) { 
    setInterval(() => {
      this.now = new Date();
    }, 1);
  }

  ngOnInit(): void {
    this.retrievedevices();
  }
/**    this.IotDataService.getAll().snapshotChanges().pipe()
      .subscribe((data) => (
       this.testes = data,
       console.log(this.testes)
     )
    ) */
    refreshList(): void {
      this.currentTutorial = null;
      this.currentIndex = -1;
      this.retrievedevices();
    }

    retrievedevices(): void {
      this.IotDataService.getAll().snapshotChanges().pipe(
        map(changes =>
          changes.map(c =>
            ({ key: c.payload.key, ...c.payload.val() })
          )
        )
      ).subscribe(data => {
        this.devices = data;
        console.log(data);
      });
    }

    setActiveTutorial(tutorial: null, index: number): void {
      this.currentTutorial = tutorial;
      this.currentIndex = index;
    }

}
