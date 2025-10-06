//ESP32 Çift Çekirdek Kullanımı
TaskHandle_t serial_task;
TaskHandle_t joystick_task;


void setup() {
  
  //Task1kodu() fonksiyonunun çalışacağı görev bloğunu öncelik 1 olarak işlemci 0'da çalışacak şekilde ayarlıyoruz
  xTaskCreatePinnedToCore( // this function 
                    serial_task_code,   /* Name of the function to be created which would implement the task. */
                    "serial_task",     /* Name of the task. */
                    10000,       /* Görev stack boyutu */
                    NULL,        /*  */
                    1,           /* Priority of the task */
                    &serial_task,/* A pointer to the task created in TaskHandle_t serial_task   */
                    0);          /*The core in which this task would happen */                  
  delay(500); 

  //Task2kodu() fonksiyonunun çalışacağı görev bloğunu öncelik 1 olarak işlemci 1'de çalışacak şekilde ayarlıyoruz
 xTaskCreatePinnedToCore( // this function 
                    joystick_task_code,   /* Name of the function to be created which would implement the task. */
                    "joystick_task",     /* Name of the task. */
                    10000,       /* Görev stack boyutu */
                    NULL,        /*  */
                    1,           /* Priority of the task */
                    &joystick_task,/* A pointer to the task created in TaskHandle_t joystick_task   */
                    0);          /*The core in which this task would happen */                  
  delay(500); 
}

void loop() { // the loop here gets automatically attached to Core 0
  // put your main code here, to run repeatedly:

}
void serial_task_code( void * pvParameters ){
/* here is supposed to be like a setup() for this specific function to run
*/

  while(1){ //in place of loop()

  } 
}

//Task2kodu: Yeşil ledi 300 ms'de bir yakıp söndüreceğiz
void joystick_task_code( void * pvParameters ){

/* here is supposed to be like a setup() for this specific function to run
*/
  while(1){ // in place of loop() 

  }
}

