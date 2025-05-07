#ifndef PioHc595_h
  #define PioHc595_h

  #include <stdbool.h>

  #include "definitions.h"

  #if GPIO_ENABLE
    #include <wiringPi.h>
    #include <unistd.h>

    class PioHc595
    {
    #define BIT_0 0x01     // padrao binario correspondente ao "bit 0".
    #define BIT_1 0x02     // padrao binario correspondente ao "bit 1".
    #define BIT_2 0x04     // padrao binario correspondente ao "bit 2".
    #define BIT_3 0x08     // padrao binario correspondente ao "bit 3".
    #define BIT_4 0x10     // padrao binario correspondente ao "bit 4".
    #define BIT_5 0x20     // padrao binario correspondente ao "bit 5".
    #define BIT_6 0x40     // padrao binario correspondente ao "bit 6".
    #define BIT_7 0x80     // padrao binario correspondente ao "bit 7".
    #define BIT_blank 0x00 // padrao para todos os bits em "0".

    private:
      const char TAB_bits[8] = {BIT_0, BIT_1, BIT_2, BIT_3, BIT_4, BIT_5, BIT_6, BIT_7};

      int total_exits;

      int pin_SCLK;
      int pin_SDOUT;
      int pin_OUTPUT;
      int pin_OUTPUT_RESSET;

      int n_reg_exits;
      char *vetor_exits;

      void EXITS_SERIAL_OUT(char DATA_8);
      short HEX16_to_BCD16(short HEX_16);

    public:
      PioHc595(void);

      void init(int pin_SCLK, int pin_SDOUT, int pin_OUTPUT, int pin_OUTPUT_RESSET, int total_exits);
      void refresh_exits(char *REG_EXITS);
      void shutdown_exits();
      void reset_exit_n(char n);
      void set_exit_n(char n);
      };
  #endif

#endif
