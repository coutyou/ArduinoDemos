/*
 电路搭建:
 * 矩阵按键连接2号引脚和+5V
 * 10kΩ电阻连接2号引脚和GND
 * 8号引脚连接8Ω扬声器
 */

#include "SCoop.h"
#include "pitches.h"

    int melody[]={
      NOTE_G4,                //5
      NOTE_E4,                //3
      NOTE_G4,                //5
      NOTE_C5,                //1.
      
      NOTE_A4,                //6
      NOTE_C5,                //1.
      NOTE_G4,                //5

      NOTE_G4,                //5
      NOTE_C4,                //1
      NOTE_D4,                //2
      NOTE_E4,                //3
      NOTE_D4,                //2
      NOTE_C4,                //1
      
      NOTE_D4,                //2
      0,

      NOTE_G4,                //5
      NOTE_E4,                //3
      NOTE_G4,                //5
      NOTE_C5,                //1.
      NOTE_B4,                //7

      NOTE_A4,                //6
      NOTE_C5,                //1.
      NOTE_G4,                //5

      NOTE_G4,                //5
      NOTE_D4,                //2
      NOTE_E4,                //3
      NOTE_F4,                //4
      NOTE_B3,                //.7
      
      NOTE_C4,                //1
      0,
    };


//持续时间函数为：

    int noteDurations[] = {
      6,12,12,3,
      6,6,3,
      6,12,12,6,12,12,
      3,3,
      6,12,12,4,12,
      6,6,3,
      6,12,12,4,12,
      3,3,
    };

// 常量，用来定义引脚号码
const int sensorPin = 2;    // 传感器的引脚
int tonePin = 8;

// 变量的声明与定义:
int sensorState;             // 记录按键的状态
int lastSensorState = LOW;   // 上一次按键的状态
int toSing = LOW;

// 以下代码以long类型声明，因为时间值以毫秒为单位(用整型会很快溢出)
long lastDebounceTime = 0;  // 按键最后一次被触发
long debounceDelay = 50;    // 为了滤去抖动暂停的时间，如果发现输出不正常增加这个值

defineTask(checkSensor);
void checkSensor::setup()
{
  pinMode(sensorPin, INPUT);
}
void checkSensor::loop()
{
    // 读取按键状态并存储到变量中:
  int reading = digitalRead(sensorPin);

  // 检查下按键状态是否改变(换句话说，输入是否是从LOW到HIGH)。
  // 检查是否距离上一次按下的时间已经足够滤去按键抖动:

  // 如果按键状态和上次不同:
  if (reading != lastSensorState) {
    // 记录初始时间
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // 离初始时间已经过了按键抖动出现的时间，因此当前的按键状态是稳定状态:

    // 如果按键状态改变了:
    if (reading != sensorState) {
      sensorState = reading;

      // 只有当稳定的按键状态时HIGH时才打开LED。
      if (sensorState == HIGH) 
      {
        toSing = !toSing;
      }
    }
  }
  
  // 保存处理结果:
  lastSensorState = reading;
}

defineTask(song);
void song::setup()
{
  
}
void song::loop()
{
  if(toSing == HIGH)
  {
    // 迭代（转悠名词）小曲中的音符:
    for (int thisNote = 0; thisNote < sizeof(melody)/sizeof(int); thisNote++) 
    {
      if(toSing == LOW)
      {
        break;
       }
      // 要根据音符种类计算播放每个音符播放的时间，只需要使用一秒除以音符的种类
      //例如，四分音符播放时间为1000 / 4,八分音符播放时间为=1000/8,以此类推。
      int noteDuration = 1500 / noteDurations[thisNote];
      tone(tonePin, melody[thisNote], noteDuration);
  
      // 为了让人耳能够分辨清楚每个音符，设置播放每个音符间的最小间隔时间。音符的播放时间*1.3作为间隔时间是比较好的选择:
      int pauseBetweenNotes = noteDuration * 1.30;
      sleep(pauseBetweenNotes);
      // stop the tone playing:
      noTone(tonePin);
    }
  }
}

void setup() {
  mySCoop.start();
}

void loop() {
  yield();
}
