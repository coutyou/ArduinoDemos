/*
  曲调

 播放一首小曲

 电路搭建:
 * LED连接13号引脚和GND
 * 矩阵按键连接2号引脚和+5V
 * 10kΩ电阻连接2号引脚和GND
 * 8号引脚连接8Ω扬声器

代码是公开的。
 */

#include "pitches.h"

    int melody[]={
   /* NOTE_A3,//.6
    NOTE_B3,//.7
           
    NOTE_C4,//1
    NOTE_C4,//1
    NOTE_B3,//.7
    NOTE_C4,//1
    NOTE_E4,//3
           
    NOTE_B3,//.7
      NOTE_B3,//.7
      NOTE_B3,//.7
      NOTE_E3,//.3

      NOTE_A3,//.6
      NOTE_A3,//.6
      NOTE_G3,//.5
      NOTE_A3,//.6
      NOTE_C4,//1

      NOTE_G3,//.5
      NOTE_G3,//.5
      NOTE_G3,//.5
      NOTE_E3,//.3

      NOTE_F3,//.4
      NOTE_F3,//.4
      NOTE_E3,//.3
      NOTE_F3,//.4
      NOTE_C4,//1
      NOTE_C4,//1

      NOTE_E3,//.3
      NOTE_E3,//.3
      NOTE_E3,//.3
      NOTE_C4,//1

      NOTE_B3,//.7
      NOTE_B3,//.7
      NOTE_FS3,//.4#
      NOTE_FS3,//.4#
      NOTE_B3,//.7

      NOTE_B3,//.7
      NOTE_B3,//.7
      0,
      NOTE_A3,//.6
      NOTE_B3,//.7

      NOTE_C4,//1
      NOTE_C4,//1
      NOTE_B3,//.7
      NOTE_C4,//1
      NOTE_E4,//3

      NOTE_B3,//.7
      NOTE_B3,//.7
      NOTE_B3,//.7
      NOTE_E3,//.3
      NOTE_E3,//.3

      NOTE_A3,//.6
      NOTE_C4,//1
      NOTE_G3,//.5
      NOTE_A3,//.6
      NOTE_C4,//1

      NOTE_G3,//.5
      NOTE_G3,//.5
      NOTE_G3,//.5
      NOTE_E3,//.3

      NOTE_F3,//.4
      NOTE_C4,//1
      NOTE_B3,//.7
      NOTE_B3,//.7
      NOTE_C4,//1

      NOTE_D4,//2
      NOTE_E4,//3
      NOTE_C4,//1
      NOTE_C4,//1
      0,

      NOTE_C4,//1
      NOTE_B3,//.7
      NOTE_A3,//.6
      NOTE_B3,//.7
      NOTE_GS3,//.5#

      NOTE_A3,//.6
      NOTE_A3,//.6
      0,
      NOTE_C4,//1
      NOTE_D4,//2
      */
      NOTE_C4,//1
      NOTE_C4,//1
      NOTE_G4,//5
      NOTE_G4,//5
      NOTE_A4,//6
      NOTE_A4,//6
      NOTE_G4,//5
      NOTE_F4,//4
      NOTE_F4,//4
      NOTE_E4,//3
      NOTE_E4,//3
      NOTE_D4,//2
      NOTE_D4,//2
      NOTE_C4,//1
      //////////
      NOTE_G4,//5
      NOTE_G4,//5
      NOTE_F4,//4
      NOTE_F4,//4
      NOTE_E4,//3
      NOTE_E4,//3
      NOTE_D4,//2
      NOTE_G4,//5
      NOTE_G4,//5
      NOTE_F4,//4
      NOTE_F4,//4
      NOTE_E4,//3
      NOTE_E4,//3
      NOTE_D4,//2
      ///////////
      NOTE_C4,//1
      NOTE_C4,//1
      NOTE_G4,//5
      NOTE_G4,//5
      NOTE_A4,//6
      NOTE_A4,//6
      NOTE_G4,//5
      NOTE_F4,//4
      NOTE_F4,//4
      NOTE_E4,//3
      NOTE_E4,//3
      NOTE_D4,//2
      NOTE_D4,//2
      NOTE_C4 //1
    };


//持续时间函数为：

    int noteDurations[42] = {
       /*8,8,
       4,8,8,4,4,
      4,4,4,4,
      4,8,8,4,4,
      4,4,4,4,
      4,8,8,8,8,4,
      4,4,4,4,
      4,8,8,4,4,
      4,4,4,8,8,
      4,8,8,4,4,
      4,4,4,8,8,
      4,8,8,4,4,
      4,4,4,4,
      4,8,8,4,4,
      4,8,4,4,8,
      8,8,4,4,4,
      4,4,4,8,8*/
      4,4,4,4,4,4,2,
      4,4,4,4,4,4,2,  
      4,4,4,4,4,4,2,
      4,4,4,4,4,4,2,
      4,4,4,4,4,4,2,
      4,4,4,4,4,4,2
    };

// 常量，用来定义引脚号码
const int buttonPin = 2;    // 连接矩阵按键的引脚
const int ledPin = 13;      // LED引脚

// 变量的声明与定义:
int ledState = HIGH;         // 记录LED的状态
int buttonState;             // 记录按键的状态
int lastButtonState = LOW;   // 上一次按键的状态

// 以下代码以long类型声明，因为时间值以毫秒为单位(用整型会很快溢出)
long lastDebounceTime = 0;  // 按键最后一次被触发
long debounceDelay = 50;    // 为了滤去抖动暂停的时间，如果发现输出不正常增加这个值

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // 设置LED初始状态
  digitalWrite(ledPin, ledState);
}

void loop() {
   // 读取按键状态并存储到变量中:
  int reading = digitalRead(buttonPin);

  // 检查下按键状态是否改变(换句话说，输入是否是从LOW到HIGH)。
  // 检查是否距离上一次按下的时间已经足够滤去按键抖动:

  // 如果按键状态和上次不同:
  if (reading != lastButtonState) {
    // 记录初始时间
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // 离初始时间已经过了按键抖动出现的时间，因此当前的按键状态是稳定状态:

    // 如果按键状态改变了:
    if (reading != buttonState) {
      buttonState = reading;

      // 只有当稳定的按键状态时HIGH时才打开LED。
      if (buttonState == HIGH) 
      {
          ledState = !ledState;
          // 迭代（转悠名词）小曲中的音符:
          for (int thisNote = 0; thisNote < 42; thisNote++) 
          {
        
            // 要根据音符种类计算播放每个音符播放的时间，只需要使用一秒除以音符的种类
            //例如，四分音符播放时间为1000 / 4,八分音符播放时间为=1000/8,以此类推。
            int noteDuration = 1000 / noteDurations[thisNote];
            tone(8, melody[thisNote], noteDuration);
        
            // 为了让人耳能够分辨清楚每个音符，设置播放每个音符间的最小间隔时间。音符的播放时间*1.3作为间隔时间是比较好的选择:
            int pauseBetweenNotes = noteDuration * 1.30;
            delay(pauseBetweenNotes);
            // stop the tone playing:
            noTone(8);
          }
      }
    }
  }

  // 设置LED:
  digitalWrite(ledPin, ledState);

  // 保存处理结果:
  lastButtonState = reading;

}
