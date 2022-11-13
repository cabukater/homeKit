import { FooterComponent } from './footer/footer.component';
import { MenuComponent } from './menu/menu.component';
import { HeaderComponent } from './header/header.component';
import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { CardsComponent } from './cards/cards.component';

@NgModule({
  declarations: [
    HeaderComponent,
    MenuComponent,
    FooterComponent,
    CardsComponent,
  ],
  imports: [
    CommonModule
  ],
  exports:[
    HeaderComponent,
    MenuComponent,
    CardsComponent
  ]
})
export class LayoutModule { }
