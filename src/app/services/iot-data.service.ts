import { Injectable } from '@angular/core';

import { AngularFireDatabase, AngularFireList } from '@angular/fire/compat/database';

@Injectable({
  providedIn: 'root'
})
export class IotDataService {

  private dbPath = '/Sensors/status';

  iotData:  AngularFireList<any>;

  constructor(db: AngularFireDatabase) {
    this.iotData = db.list(this.dbPath);

     }

     getAll(): AngularFireList<any> {
      return this.iotData;
    }

}
