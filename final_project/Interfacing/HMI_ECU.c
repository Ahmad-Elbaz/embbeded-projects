/*
 * ===============================================
 * HMI_ECU.c
 *
 *      Author: Ahmed Adel Elbaz
 * ================================================
 */
#include "HMI_ECU.h"

const UART_ConfigType UART_CONFIG = {Asynchronous,disabled,defult,_1bit,_8bit};

uint8 g_pass1[10] , g_pass2[10], g_userPass[10];



int main(void){
	uint8 data1 = 0;
	UART_init(&UART_CONFIG);
	LCD_init();

	for(;;)
	{
		LCD_clearScreen();
		data1= receiveByte();
		Timer1_delay_10msec();
		Timer1_delay_10msec();
		/*
		 * to do action upon what received from control_ECU in data1
		 */
		switch(data1)
		{
		/*case receive from control_ECU enter new pass*/
		case ENTER_NEW_PASS:
			enterPass((uint8 *)"Enter new pass",g_pass1);
			data1 = FREE;
			break;
		case CONFIRM_PASS:
			enterPass((uint8 *)"Confirm pass",g_pass2);
			data1 = FREE;
			break;
		case NO_MATCH:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,(char*)"    PASSWORD    ");
			LCD_displayStringRowColumn(1,0,(char*)"  DO NOT MATCH  ");
			Timer1_delay_sec();
			Timer1_delay_sec();
			data1 = FREE;
			break;
		case PASS_SAVED:
			LCD_clearScreen();
			LCD_displayString((char*)"   PASS SAVED   ");
			Timer1_delay_sec();
			Timer1_delay_sec();
			data1 = FREE;
			break;
		case MAIN_MENU:
			/*print the main menu and send the input char to control_ECU*/
			mainMenu();
			data1 = FREE;
			break;
		case ENTER_PASS:
			enterPass((uint8 *)"Enter pass",g_userPass);
			freeStr(g_userPass,20);
			data1 = FREE;
			break;

		case WRONG_CHOICE:
			data1 = FREE;
			break;
		case ENTER_OLD_PASS:
			enterPass((uint8 *)"Enter old pass",g_userPass);
			freeStr(g_userPass,20);
			data1 = FREE;
			break;
		case YOU_HAVE_1_TRIES:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,(char*)"1 TRIES left");
			Timer1_delay_sec();
			enterPass((uint8 *)"Enter pass",g_userPass);
			freeStr(g_userPass,20);
			data1 = FREE;
			break;
		case YOU_HAVE_2_TRIES:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,(char*)"YOU HAVE 2 TRIES");
			Timer1_delay_sec();
			enterPass((uint8 *)"Enter pass",g_userPass);
			freeStr(g_userPass,20);
			data1 = FREE;
			break;
		case LOCKING:
			locking();
			data1 = FREE;
			break;
		case OPEN_DOOR:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,(char*)"door is opening");
			Timer1_delay_sec();
			Timer1_delay_sec();
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,(char*)"door is open");
			Timer1_delay_sec();
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,(char*)"door is closing");
			Timer1_delay_sec();
			Timer1_delay_sec();
			data1 = FREE;
			break;
		default:
			LCD_clearScreen();
			LCD_displayString((char*)"default");
			Timer1_delay_sec();
			break;
		}
	}
	return 0;
}

/*
 * wait until the control_ECU to be ready to send the byte
 * and send data to the Control_ECU
 */
void sendByte(uint8 a_data){
	/* Wait until control_ECU is ready to receive the byte */
	while(UART_recieveByte() != CONTROL_READY) {}

	/* Send the required byte to control_ECU through UART */
	UART_sendByte(a_data);
}

/* - function to tell the control_ECU i'm ready
 * - receive byte from control_ECU*/
uint8 receiveByte(void){
	uint8 recieveData;
	/* Send HMI_READY byte to control_ECU to ask it to send the data */
	UART_sendByte(HMI_READY);

	/* Receive byte from contorl_ECU through UART */
	recieveData = UART_recieveByte();
	return recieveData;
}

/*wait until the control ECU ready and send string*/
void sendString(const uint8 *a_str){
	/* Wait until Control_ECU is ready to receive the string */
	while(UART_recieveByte() != CONTROL_READY) {}

	/* Send the required string to MC2 through UART */
	UART_sendString(a_str);
}
/*
 * display required message
 * receive the new pass
 * send the new pass to control_ECU
 */
void enterPass(uint8 * a_lcdMessage,uint8 * a_returnPass){
	LCD_clearScreen();
	LCD_displayString((char*)a_lcdMessage);
	/*get the password with keypad and save it in g_pass1*/
	getPass(a_returnPass);
	/*send the first pass to control_ECU */
	sendString(a_returnPass);
}
/*get password from user with keypad and save it*/
void getPass( uint8 * const a_str){
	uint8 i=0,key=0;
	Timer1_delay_sec();
	key= KEYPAD_getPressedKey();
	while(key != 13)
	{
		a_str[i]= key; //save pass in string
		/*move cursor to print (*) instead of pass in second line*/
		LCD_moveCursor(1,i);
		LCD_displayCharacter('*');
		i++;
		/*wait until the user release the button*/
		Timer1_delay_sec();
		key= KEYPAD_getPressedKey();
	}
	/*make the last char '#' to send it with uart to control_ECU*/
	a_str[i]= (uint8)'#' ;
}
/*===========================================================*/
void mainMenu(void){
	uint8 key=0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,(char*)" + open door    ");
	LCD_displayStringRowColumn(1,0,(char*)" - change pass  ");


	Timer1_delay_sec();
	key= KEYPAD_getPressedKey();
	/*if the input char is not '+' nor '-' ask to input again*/
	while(key != '+' && key != '-')
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,(char*)" Wrong choice    ");
		Timer1_delay_sec();
		Timer1_delay_sec();
		/*display main menu*/
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,(char*)" + open door    ");
		LCD_displayStringRowColumn(1,0,(char*)" - change pass  ");
		/*get the key*/
		key= KEYPAD_getPressedKey();
	}
	Timer1_delay_10msec();
	/*send the choice to control_ECU*/
	sendByte(key);
}

void freeStr(uint8 * str,uint8 str_size){
	for(uint8 i=0;i<str_size;i++)
	{
		str[i]=0;
	}
}

void locking(void){
	for(uint8 i=0;i<23;i++)
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,(char*)"   the system is locked  ");
		Timer1_delay_sec();
		LCD_clearScreen();
		Timer1_delay_sec();
	}
}














