#include "gpio.h"

GPIO* GPIO::instance()
{
    static GPIO instance;

    return &instance;
}

bool GPIO::initialize(void)
{
	#if GPIO_ENABLE
		if( wiringPiSetup() ) 
		{
			//registers
			mPioHc595.init(26, 0, 2, 3, 16);    //pino_SCLK, pino_SDOUT, pino_OUTPUT, pino_OUT_RESSET, total_SAIDAS
			mPioHc595.shutdown_exits();
			
			//ios
			pinMode(KEYUP, INPUT);
			pinMode(KEYDOWN, INPUT);
			pinMode(KEYLEFT, INPUT);
			pinMode(KEYRIGHT, INPUT);
			
			pullUpDnControl(KEYUP, PUD_DOWN);
			pullUpDnControl(KEYDOWN, PUD_DOWN);
			pullUpDnControl(KEYLEFT, PUD_DOWN);
			pullUpDnControl(KEYRIGHT, PUD_DOWN);

			return true;
		}

		return false;
	#else
    	return true;
	#endif
}

int GPIO::pin_read(int pin)
{
	#if GPIO_ENABLE
		return digitalRead(pin);
	#else
		return 0;
	#endif
}
	
void GPIO::pin_write(int pin, int value)
{
	#if GPIO_ENABLE
		digitalWrite(pin, value);
	#endif
}

void GPIO::matrix_test()
{
	#if GPIO_ENABLE
		mPioHc595.shutdown_exits();

		for (int i = 1; i <= (MATRIX_NUM_ROWS*MATRIX_NUM_COLS); i++)
		{		
			mPioHc595.set_exit_n((char)i);   // liga a saida, e assim o LED conectado nela.
			delay(500);   // tempo que fica ligado.
			mPioHc595.shutdown_exits();
		}
	#endif
}

void GPIO::matrix_print_signal(int arr[])
{
	#if GPIO_ENABLE
		mPioHc595.shutdown_exits();
	#endif

	this->signal = 0;

	for (int i = 0; i < MATRIX_NUM_ROWS; i++)
	{
		for (int j = 0; j < MATRIX_NUM_COLS; j++)
		{
			this->signal++;

			if (arr[(MATRIX_NUM_COLS * j) + i] != 0)
			{
				#if GPIO_ENABLE
					mPioHc595.set_exit_n(this->signal);
					delay(10);
				#endif
			}

			cout << arr[(MATRIX_NUM_COLS * j) + i] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void GPIO::matrix_print_tacton(vector<int *> tacton, float time)
{
	for (int i = 0; i < (int)tacton.size(); i++) 
    {
       this->matrix_print_signal(tacton[i]);

		#if GPIO_ENABLE
	   		delay(time);  //tempo entre cada frame do tacton
		#endif
	}
}

int GPIO::process_input()
{
	if (pin_read(KEYUP) == 1) 
	{  
		return KEYUP;
	}  
	
	if (pin_read(KEYDOWN) == 1) 
	{  
		return KEYDOWN;
	}
	
	if (pin_read(KEYLEFT) == 1) 
	{  
		return KEYLEFT;
	}
	
	if (pin_read(KEYRIGHT) == 1) 
	{  
		return KEYRIGHT;
	}
	
	return INT_MAX;
}
