#include "ParallaxDisplay.h"
#include <math.h>

#define PARALLAX_LCD_ROWS 2
#define PARALLAX_LCD_COLS 16

ParallaxDisplay::ParallaxDisplay(HardwareSerial* port) :
    CMD_MOVE_LEFT((char)8),
    CMD_MOVE_RIGHT((char)9),
    CMD_MOVE_DOWN((char)10),
    CMD_CLEAR((char)12),
    CMD_BACKLIGHT_ON((char)17),
    CMD_BACKLIGHT_OFF((char)18),
    CMD_DISPLAY_OFF((char)21),
    CMD_DISPLAY_ON_NOCURSOR_NOBLINK((char)22),
    CMD_DISPLAY_ON_NOCURSOR_BLINK((char)23),
    CMD_DISPLAY_ON_CURSOR_NOBLINK((char)24),
    CMD_DISPLAY_ON_CURSOR_BLINK((char)25),
    CMD_MOVE_L0((char)128),
    CMD_MOVE_L1((char)148)
{
    serial_port = port;

    (*serial_port).begin(19200);

    pos_row = 0;
    pos_col = 0;
    light = true;
    blink = false;
    cursor = false;
    screen = true;

    move_to(0,0);

    update_screen_config();
    clear();
}

void ParallaxDisplay::wrap_position()
{
    pos_row += floor(pos_col / PARALLAX_LCD_COLS);
    pos_col = pos_col % PARALLAX_LCD_COLS;
    pos_row = pos_row % PARALLAX_LCD_ROWS;
}


void ParallaxDisplay::move_left()
{
    (*serial_port).print(CMD_MOVE_LEFT);
    pos_col--;
    wrap_position();
}

void ParallaxDisplay::move_right()
{
    (*serial_port).print(CMD_MOVE_RIGHT);
    pos_col++;
    wrap_position();
}

void ParallaxDisplay::move_down()
{
    (*serial_port).print(CMD_MOVE_DOWN);
    pos_row++;
    wrap_position();
}

void ParallaxDisplay::move_up()
{
    (*serial_port).print(CMD_MOVE_DOWN);
    pos_row--;
    wrap_position();
}

void ParallaxDisplay::move_to(int row, int col)
{
    pos_row = row;
    pos_col = col;
    wrap_position();
    char move_cmd = (pos_row == 0? CMD_MOVE_L0 : CMD_MOVE_L1);
    move_cmd = (char)(((int)move_cmd) + pos_col);
    (*serial_port).print(move_cmd);
}

void ParallaxDisplay::write_at(int row, int col, char message[])
{
    int old_row = pos_row;
    int old_col = pos_col;

    move_to(row, col);
    write(message);
    move_to(old_row, old_col);
}

void ParallaxDisplay::write_at(int row, int col, int number)
{
    char buf[intlen(number)];
    sprintf(buf, "%i", number);
    write_at(row, col, buf);
}

void ParallaxDisplay::write(char message[])
{
    (*serial_port).print(message);
    pos_col += strlen(message);
    wrap_position();
}

void ParallaxDisplay::write(int number)
{
    char buf[intlen(number)];
    sprintf(buf, "%i", number);
    write(buf);
}

void ParallaxDisplay::write_centered(int row, char message[])
{
    int length = strlen(message);
    if (length > PARALLAX_LCD_COLS) {
        for (int i = 0; i < PARALLAX_LCD_COLS; i++) {
            write_at(row, i, "x");
        }
    } else {
        int left = floor((PARALLAX_LCD_COLS - length) / 2.0);
        clear_row(row);
        write_at(row, left, message);
    }
}

void ParallaxDisplay::write_centered(int row, int number)
{
    char buf[intlen(number)];
    sprintf(buf, "%i", number);
    write_centered(row, buf);
}

void ParallaxDisplay::light_on()
{
    light = true;
    update_screen_config();
}

void ParallaxDisplay::light_off()
{
    light = false;
    update_screen_config();
}

void ParallaxDisplay::blink_on()
{
    blink = true;
    update_screen_config();
}
void ParallaxDisplay::blink_off()
{
    blink = false;
    update_screen_config();
}

void ParallaxDisplay::cursor_on()
{
    cursor = true;
    update_screen_config();
}
void ParallaxDisplay::cursor_off()
{
    cursor = false;
    update_screen_config();
}

void ParallaxDisplay::screen_on()
{
    screen = true;
    update_screen_config();
}
void ParallaxDisplay::screen_off()
{
    screen = false;
    update_screen_config();
}

void ParallaxDisplay::update_screen_config()
{
    if (light) {
        (*serial_port).print(CMD_BACKLIGHT_ON);
    } else {
        (*serial_port).print(CMD_BACKLIGHT_OFF);
    }

    if (!screen) {
        (*serial_port).print(CMD_DISPLAY_OFF);
    } else {
        if (cursor && blink) {
            (*serial_port).print(CMD_DISPLAY_ON_CURSOR_BLINK);
        } else if (cursor && !blink) {
            (*serial_port).print(CMD_DISPLAY_ON_CURSOR_NOBLINK);
        } else if (!cursor && blink) {
            (*serial_port).print(CMD_DISPLAY_ON_NOCURSOR_BLINK);
        } else {
            (*serial_port).print(CMD_DISPLAY_ON_NOCURSOR_NOBLINK);
        }
    }
}

void ParallaxDisplay::clear_row(int row)
{
    for (int i = 0; i < PARALLAX_LCD_COLS; i++) {
        write_at(row, i, " ");
    }
}

void ParallaxDisplay::clear()
{
    (*serial_port).print(CMD_CLEAR);
}

int ParallaxDisplay::intlen(int number)
{
    int end = 0;
    while(number >= 1) {
        number = number/10;
        end++;
    }
    return end;
}
