/*
 * ===========================================================
 * control_ECU.c
 *
 *      Author: Ahmed Adel Elbaz
 * ===========================================================
 */
#include "control_ECU.h"


const UART_ConfigType UART_CONFIG = {Asynchronous,disabled,defult,_1bit,_8bit};

uint8 g_pass1[10] , g_pass2[10] , g_savedPass[10], g_wrongPassCount =0;


int main(void){
	UART_init(&UART_CONFIG);
	LCD_init();
	Buzzer_Init();
	DcMotor_Init();

	GPIO_setupPinDirection(PORTA_ID,PIN0_ID,PIN_OUTPUT);


	firstTimeMenu();
while(1)
	{
		mainMenu();
	}
	return 0;
}
/*display the first time settings when the user use the program for the first time*/
void firstTimeMenu(void){
	do
	{
		/*-ask HMI to display "Enter new pass
		 *-receive the pass
		 *-send the pass back*/
		sendByte(ENTER_NEW_PASS);
		/*receive first pass from the user*/
		receiveString(g_pass1);
		/*
		 * ask HMI to confirm the pass again
		 * and send the confirmed pass back
		 */
		sendByte(CONFIRM_PASS);
		/*receive second pass from the user*/
		receiveString(g_pass2);
		/*if the two pass do not match display pass not match*/
		if(strcmp(g_pass1,g_pass2)){sendByte(NO_MATCH);}

	}while(strcmp(g_pass1,g_pass2));
	/*ask the HMI to display pass saved*/
	sendByte(PASS_SAVED);
	strcpy(g_savedPass,g_pass2);


	/*clear the pass in g_pass1 & g_pass2
	 * so when i use them again they don't contain the correct pass*/
	for(uint8 i=0;i<20;i++)
	{
		g_pass1[i]=0;
		g_pass2[i]=0;
	}

}

/*
 * wait until the HMI_ECU to be ready to send the byte
 * and send data to the HMI_ECU
 */
void sendByte(uint8 a_data){
	/* Wait until HMI is ready to receive the byte */
	while(UART_recieveByte() != HMI_READY) {}

	/* Send the required byte to HMI through UART */
	UART_sendByte(a_data);
}
/* - function to tell the HMI_ECU i'm ready
 * - receive byte from HMI_ECU*/
uint8 receiveByte(void){
	uint8 recieveData;
	/* Send CONTROL_READY byte to HMI to ask it to send the data */
	UART_sendByte(CONTROL_READY);

	/* Receive byte from HMI_ECU through UART */
	recieveData = UART_recieveByte();
	return recieveData;
}

void receiveString(uint8 * a_string){
	/* Send Control_READY byte to HMI_ECU to ask it to send the string */
	UART_sendByte(CONTROL_READY);

	/* Receive String from MC1 through UART */
	UART_receiveString(a_string);
}

/*==========================================================================*/
void mainMenu(void){
	uint8 choice;
	/*get the saved pass from the eeprom and save it in g_pass1*/
	//eepromReadStr(g_savedPass);
	/*
	 * ask the HMI to display the main menu ( (+) open door (-) change pass)
	 * and send '+' or '-' back
	 */

	sendByte(MAIN_MENU);
	/*receive user choice (+) or (-) from the HMI_ECU*/
	choice = receiveByte();
	/*
	 * this short if just display on lcd (enter pass or enter old pass)depend on
	 * if open door -> enter pass
	 * if change pass -> enter old pass
	 */
	choice =='+'?askOldPass(ENTER_PASS):askOldPass(ENTER_OLD_PASS);
	/*
	 * isCorrectPass() -> compare the entered pass g_pass2 with the saved one
	 * if match return true if not return false
	 */
	if(! isCorrectPass())
	{
		/*count how many times the user enter the pass wrong*/
		g_wrongPassCount++;
		for(uint8 i=0;i<2;i++)
		{
			/*to check how many tries left*/
			if(i==0)
			{askOldPass(YOU_HAVE_2_TRIES);}
			else
			{askOldPass(YOU_HAVE_1_TRIES);}
			/*if the user enter the correct pass break the for(i=0;i<2;i++)*/
			if(isCorrectPass())
			{
				break;
			}else
			{
				g_wrongPassCount++;
			}
		}


	}



	/*check if the pass enter max wrong times */
	if(g_wrongPassCount >= 3)
	{
		locking();
	}else
	{
		switch (choice)
		{
		case'+':
			openDoor();
			break;
		case'-':
			firstTimeMenu();
			break;
		default:
			/*ask the HMI_ECU to display WRONG_CHOICE*/
			sendByte(WRONG_CHOICE);
			break;
		}
		g_wrongPassCount =0;
	}


}
void askOldPass(uint8 message){
	/*-ask HMI to display "message"
	 *-receive the pass
	 *-send the pass back and save it in g_pass2*/
	sendByte(message);
	/*receive the input pass from user through uart*/
	receiveString(g_pass2);
}
void openDoor(){
	sendByte(OPEN_DOOR);
	/*open door for 3 seconds*/
	DcMotor_Rotate(CW,250);
	Timer1_delay_sec();
	Timer1_delay_sec();
	/*keep the door open for 2 seconds*/
	DcMotor_Rotate(stop,0);
	Timer1_delay_sec();/*close the door*/
	DcMotor_Rotate(CCW,250);
	Timer1_delay_sec();
	Timer1_delay_sec();
	DcMotor_Rotate(stop,0);
}
/*
 * check if the pass user enter which saved in g_pass2 is the same g_savedPass->(from eeprom)
 * and set the g_pass2 equal zero before return true if match false if not
 */
boolean isCorrectPass(){
	uint8 i=0;
	/*loop with length of g_savedPass as it is the correct one*/
	while(g_savedPass[i] != '\0')
	{
		/*if the pass don't match return false*/
		if(g_savedPass[i] != g_pass2[i])
		{
			freeStr(g_pass2,20);
			return FALSE;
		}
		i++;
	}
	/*if the pass match return true*/
	freeStr(g_pass2,20);
	return TRUE;
}

void locking(void){
	sendByte(LOCKING);
	Buzzer_On();
	Timer1_delay_sec();
	Timer1_delay_sec();
	Timer1_delay_sec();
	Buzzer_Off();
}
void freeStr(uint8 * str,uint8 str_size){
	for(uint8 i=0;i<str_size;i++)
	{
		str[i]=0;
	}
}

void eepromWriteStr(uint8 * str){
	uint8 i=0 ;
	uint16 startAddress = (uint16)0x1111;
	while(str[i] != '\0')
	{
		EEPROM_writeByte((uint16)startAddress+i,str[i]);
		Timer1_delay_10msec();
		Timer1_delay_10msec();
		i++;
	}
	EEPROM_writeByte(startAddress+i,'#');
	Timer1_delay_10msec();
	Timer1_delay_10msec();
}

void eepromReadStr(uint8 * str){
	uint8 i=0 ;
	uint16 startAddress = (uint16)0x01;
	uint8 data;
	EEPROM_readByte(startAddress+i,&data);
	while(data !='#')
	{
		str[i]=data;
		i++;
		EEPROM_readByte(startAddress+i,&data);
		Timer1_delay_10msec();
		Timer1_delay_10msec();
	}
	str[i] = '\0';
}

