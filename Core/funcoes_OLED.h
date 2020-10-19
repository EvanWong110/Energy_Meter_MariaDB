/* * Nome do arquivo: funcoes_OLED.h
 *  Este arquivo possui as funcoes relacionadas ao display oled
 *  
 */

#define SW_DISPLAY D4              // Chave para mudança de tela
#define SDA_PIN D1                 // display Pin
#define SCK_PIN D2                 // display Pin
#define LEDPIN D3

SSD1306Wire display(0x3c, SDA_PIN, SCK_PIN);

void displayInit(){                 //Inicializa o display
  display.init();
  display.flipScreenVertically();
  display.clear();
}

void display_msg(String texto){     // Envia mensagens diversas para o display
  display.clear();
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString((display.getWidth()/2), (display.getHeight()/2), texto);
  display.display();
}

void displayUpdate(int * current_view){                                      // Atualiza dados do display  
  display.clear();                                                                                
  display.setTextAlignment(TEXT_ALIGN_CENTER);                                                    
  display.setFont(ArialMT_Plain_16);                                                              
  display.drawRect(0, 0, display.getWidth(), display.getHeight());               // Retangulo principal borda branca
  display.fillRect(0, 0, display.getWidth(), (display.getHeight()/2)-8);         // Retangulo interno preenchimento branco
  char parametro[20], medicao[20];
  switch(* current_view){
    case 0:
        strcpy(parametro, "Tensão");
        sprintf(medicao, "%.2f V",atual.tensao);
    break;
    case 1:
        strcpy(parametro, "Corrente");
        sprintf(medicao, "%.2f A",atual.corrente);
    break;
    case 2:
        strcpy(parametro, "Pot. AT");
        sprintf(medicao, "%.2f W",atual.pot_at);
    break;
    case 3:
        strcpy(parametro, "Pot. RE");
        sprintf(medicao, "%.2f VAr",atual.pot_re);
    break;
    case 4:
        strcpy(parametro, "Pot. AP");
        sprintf(medicao, "%.2f VA",atual.pot_ap);
    break;
    case 5:
        strcpy(parametro, "ID");
        sprintf(medicao, "%s",atual.id);
    break;
    case 6:
        strcpy(parametro, "FREQ");
        sprintf(medicao, "%.2f Hz",atual.frequencia);    
    break;
    case 7:
        strcpy(parametro, "FP");
        sprintf(medicao, "%.2f",atual.FP);    
    break;
    default:
    * current_view = 0;
  }
  
  display.setColor(BLACK);                                                       
  display.drawString((display.getWidth()/2),5,parametro);   // Imprime o nome do parametro
  display.setColor(WHITE);                                                       
  display.drawString((display.getWidth()/2),(display.getHeight()/2), medicao); // Imprime o valor com a unidade de medida
  display.display();
}

void piscaled(int quantidade, int tempo){
  int i;
  for (i=0; i<quantidade; i++){
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LEDPIN, LOW);
    delay(tempo);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LEDPIN, HIGH);
    delay(tempo);
  }
}
