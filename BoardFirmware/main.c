#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "usb_flash.h"
#include "pins.h"

__IO uint8_t PrevXferComplete = 1;

uint8_t AES_key[SESSION_KEY_LEN] = { 0x48,0x65,0x6c,0x6c,0x6f,0x2c,0x20,0x77,0x6f,0x72,0x6c,0x64,0x21,0x21,0x21,0x21 };
uint8_t cryptmess[CIPHER_SESSION_KEY_LEN];

uint8_t userPorts[2]; //Входы[0] / выходы[1] определенные пользователем. Каждый бит -это вход или выход.

//Мигаем светодиодом заданное количество раз.
void flash_LED(uint8_t count)
{
	int i = 0;
	while(i < count)
	{
		GPIO_ResetBits(LED_PORT, GPIO_Pin_13); //Светодиод подключен к плюсу – поэтому это его засветит.
		delay(3000000);	
		GPIO_SetBits(LED_PORT, GPIO_Pin_13);	
		delay(3000000);
		i++;
	}		
}	

int main(void)
{
	FLASH_Init();
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);	
	Set_System();

  Set_USBClock();
	USB_Init();
 	USB_Interrupts_Config();
	
	for (int i =0; i < sizeof(cryptmess); ++i) cryptmess[i] = 0x00;
	
	userPorts[0] = 0; 
	userPorts[1] = 0x01; // Синий светодиод включен.

	//flash_LED(5);	
	while(1)
	{
		delay(1000);
		
		if(userPorts[1] & 0x01 == 1)
		{
			GPIO_ResetBits(LED_PORT, GPIO_Pin_13); //Светодиод подключен к плюсу – поэтому это его засветит.
		}
		else
		{
			GPIO_SetBits(LED_PORT, GPIO_Pin_13);	
		}
		
		//С помощью функции из SPL(устарел) считываем из внешнего мира состояние кнопки.
		userPorts[0] = GPIO_ReadInputDataBit(BUTTON_PORT, BUTTON_PIN);
	}
}
