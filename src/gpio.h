#ifndef GPIO_h
	#define GPIO_h

	//BUTONS
	#define KEYUP 10
	#define KEYDOWN 11
	#define KEYLEFT 6
	#define KEYRIGHT 31

	#include <iostream>
	#include <bits/stdc++.h>
	#include <limits.h>
	#include <stdbool.h>

	#include "definitions.h"

	#if GPIO_ENABLE
		#include <wiringPi.h>
		#include "PioHc595.h"
	#endif

	using namespace std;

	class GPIO
	{		
		private:
			char signal = 0;

			//Singleton
			GPIO(){}
			~GPIO(){}

			GPIO(const GPIO& rhs);
			GPIO& operator=(const GPIO& rhs);
			
			int pin_read(int pin);
			void pin_write(int pin, int value);
			
		public:
			#if GPIO_ENABLE
				PioHc595 mPioHc595;
			#endif

			static GPIO *instance();

			bool initialize(void);

			void matrix_test();
			void matrix_print_signal(int arr[]);
			void matrix_print_tacton(vector<int *> tacton, float time = 500);

			int process_input();
	};

#endif