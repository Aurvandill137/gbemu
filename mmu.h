//
// Created by Ole H. on 12.05.2019.
//

#ifndef GBEMU_MMU_H
#define GBEMU_MMU_H

#define INTERUPPTFLAGS 0xFF0F
#define INTERUPTENABLE 0xFFFF
#define DIVIDERREGISTER 0xFF04
#define TIMERCOUNTER 0xFF05
#define TIMERMODULO 0xFF06
#define TIMERCONTROL 0xFF07H
#define JOYPAD 0xFF00

#define LCD_CONTROL 0xFF40
#define LCD_STATUS 0xFF41
#define LCD_SCROLL_Y 0xFF42
#define LCD_SCROLL_X 0xFF43
#define LCD_Y_COORDINATE 0xFF43

#define VRAM_START 0x8000
#define VRAM_END 0x9FFF

#define TIMER_DIVIDER 0xFF04
#define TIMER_COUNTER 0xFF05
#define TIMER_MODULO 0xFF06
#define TIMER_CONTROL 0xFF07

#define INTERRUPT_ENABLE 0xFFFF
#define INTERRUPT_FLAG 0xFF0F

// 7,6,5,4,3,2,1,0
//ROW1: Start,Select,B,A
//ROW2: Down,Up,Left,Right
//note that 0 means pressed so we need to invert the register afterwards
//7: -
//6: -
//5: ROW2
//4: ROW1
//3: Start,Down
//2: Select,Up
//1: B,Left
//0: A,Right

#define JOY_START 0b00011000
#define JOY_SELECT 0b00010100
#define JOY_B 0b00010010
#define JOY_A 0b00010001
#define JOY_DOWN 0b00101000
#define JOY_UP 0b00100100
#define JOY_LEFT 0b00100010
#define JOY_RIGHT 0b00100001




void write_address(uint8_t data, uint16_t address);
unsigned char read_address(uint16_t address);

#endif //GBEMU_MMU_H
