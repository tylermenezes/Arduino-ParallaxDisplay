#ifndef PARALLAXDISPLAY_H
#define PARALLAXDISPLAY_H
#include <HardwareSerial.h>

class ParallaxDisplay {
  private:
      const char CMD_MOVE_LEFT;
      const char CMD_MOVE_RIGHT;
      const char CMD_MOVE_DOWN;
      const char CMD_CLEAR;
      const char CMD_BACKLIGHT_ON;
      const char CMD_BACKLIGHT_OFF;
      const char CMD_DISPLAY_OFF;
      const char CMD_DISPLAY_ON_NOCURSOR_NOBLINK;
      const char CMD_DISPLAY_ON_NOCURSOR_BLINK;
      const char CMD_DISPLAY_ON_CURSOR_NOBLINK;
      const char CMD_DISPLAY_ON_CURSOR_BLINK;
      const char CMD_MOVE_L0;
      const char CMD_MOVE_L1;

      int pos_row;
      int pos_col;
      bool light;
      bool blink;
      bool cursor;
      bool screen;

      HardwareSerial* serial_port;

      void wrap_position();
      void update_screen_config();

      int intlen(int number);

  public:
      ParallaxDisplay(HardwareSerial* port);

      void move_left();
      void move_right();
      void move_down();
      void move_up();
      void move_to(int row, int col);

      void write_at(int row, int col, char message[]);
      void write_at(int row, int col, int number);

      void write_centered(int row, char message[]);
      void write_centered(int row, int number);

      void write(char message[]);
      void write(int number);

      void light_on();
      void light_off();

      void blink_on();
      void blink_off();

      void cursor_on();
      void cursor_off();

      void screen_on();
      void screen_off();

      void clear_row(int row);
      void clear();
};
#endif
