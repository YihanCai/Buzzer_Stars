#include "stm32f10x.h"
#include "delay.h"

// 音符频率定义 (Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_REST 0

// 节拍定义 (ms)
#define BEAT_QUARTER 400
#define BEAT_HALF    800

// 播放音符函数
void PlayNote(uint16_t frequency, uint16_t duration) {
    if (frequency == NOTE_REST) {
        // 休止符，保持静音
        GPIO_SetBits(GPIOB, GPIO_Pin_12);
        Delay_ms(duration);
    } else {
        // 计算半周期时间 (微秒)
        uint32_t half_period = 500000 / frequency;
        uint32_t cycles = (duration * 1000) / (2 * half_period);
        
        for (uint32_t i = 0; i < cycles; i++) {
            GPIO_ResetBits(GPIOB, GPIO_Pin_12);
            Delay_us(half_period);
            GPIO_SetBits(GPIOB, GPIO_Pin_12);
            Delay_us(half_period);
        }
    }
}

int main(void) {
    GPIO_InitTypeDef GPIO_Initstructure;
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   
    GPIO_Init(GPIOB, &GPIO_Initstructure);
    
    // 小星星旋律
    uint16_t melody[] = {
        NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_REST,
        NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_REST,
        NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_REST,
        NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_REST,
        NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_REST,
        NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_REST
    };
    
    uint16_t durations[] = {
        BEAT_QUARTER, BEAT_QUARTER, BEAT_QUARTER, BEAT_QUARTER, 
        BEAT_QUARTER, BEAT_QUARTER, BEAT_HALF, BEAT_QUARTER,
        BEAT_QUARTER, BEAT_QUARTER, BEAT_QUARTER, BEAT_QUARTER, 
        BEAT_QUARTER, BEAT_QUARTER, BEAT_HALF, BEAT_QUARTER,
        BEAT_QUARTER, BEAT_QUARTER, BEAT_QUARTER, BEAT_QUARTER, 
        BEAT_QUARTER, BEAT_QUARTER, BEAT_HALF, BEAT_QUARTER,
        BEAT_QUARTER, BEAT_QUARTER, BEAT_QUARTER, BEAT_QUARTER, 
        BEAT_QUARTER, BEAT_QUARTER, BEAT_HALF, BEAT_QUARTER,
        BEAT_QUARTER, BEAT_QUARTER, BEAT_QUARTER, BEAT_QUARTER, 
        BEAT_QUARTER, BEAT_QUARTER, BEAT_HALF, BEAT_QUARTER,
        BEAT_QUARTER, BEAT_QUARTER, BEAT_QUARTER, BEAT_QUARTER, 
        BEAT_QUARTER, BEAT_QUARTER, BEAT_HALF, BEAT_QUARTER
    };
    
    uint8_t melody_length = sizeof(melody) / sizeof(melody[0]);
    
    while(1) {
        // 播放整首旋律
        for (uint8_t i = 0; i < melody_length; i++) {
            PlayNote(melody[i], durations[i]);
            Delay_ms(50); // 音符间的小间隔
        }
        
        // 曲子间的长间隔
        Delay_ms(2000);
    }
}