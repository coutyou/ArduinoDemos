/*
做的一个利用超声波传感器检测距离，控制风扇开关的装置
并且可以利用按钮开关整个装置，led用于表现装置的开关
*/

#define IApin 2 //设置L9110电机控制板IA口与arduino pin2连接

#define IBpin 3 //设置L9110电机控制板IA口与arduino pin3连接

const int TrigPin = 4; //超声波发射端接4

const int EchoPin = 5; //超声波接收端接5

float cm;

const int  buttonPin = 6; //按钮接6

const int ledPin = 7;//led接7

int buttonPushCounter = 0;  //初始化计数

int buttonState = 0; //初始化按钮状态      

int lastButtonState = 0; //初始化上一次按钮状态

int flag = 0;//初始化检测数

int lastflag = 0;//初始化上一次的检测数

int delaytime = 100;//休息0.1秒

void setup()//初始化函数

{
  
  Serial.begin(9600); 

  pinMode(buttonPin, INPUT);//设置输出输入

  pinMode(ledPin, OUTPUT);
  
  pinMode(TrigPin, OUTPUT); 
  
  pinMode(EchoPin, INPUT);
  
  pinMode (IApin, OUTPUT); //设置arduino pin2 为输出引脚，作为L9110电机控制板的TTL输入信号

  pinMode (IBpin, OUTPUT); //设置arduino pin3 为输出引脚，作为L9110电机控制板的TTL输入信号

}

void loop()//循环函数

{
     
  buttonState = digitalRead(buttonPin);//获得目前的按钮状态

  if (buttonState != lastButtonState) {//与上个状态比较

    if (buttonState == HIGH) {//由不按改变为按的话 输出次数
   
      buttonPushCounter++;
      Serial.println();
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {//由按改变为不按的话 输出空
      Serial.println();
    }

  }
  
  lastButtonState = buttonState;//更新状态

  if(buttonPushCounter==0)//刚刚连接的情况
  {

    
    }

  if((buttonPushCounter>=1)&&(buttonPushCounter%2==1))//亮灯开启
  {
  
  digitalWrite(ledPin, HIGH);//点亮led

  digitalWrite(TrigPin, LOW); //输出两毫秒低电平信号

  delayMicroseconds(2); 

  digitalWrite(TrigPin, HIGH);//输出十毫秒高电平信号

  delayMicroseconds(10);

  digitalWrite(TrigPin, LOW);//输出低电平

  cm = pulseIn(EchoPin, HIGH) / 58; //读取回波时间 将回波时间换算成cm

  cm = (int(cm * 100)) / 100; //保留两位小数

  Serial.print("距离为：");

  Serial.print(cm);

  Serial.println("cm");//串口输出 

  if (cm<=30)//距离小于三十厘米
{
  flag = 1;

  if(lastflag!=flag)//风扇状态改变
  {
    
    Serial.println("风扇开启！！！");

    lastflag=1;
  
  }
  
  digitalWrite (IApin, HIGH); //IA口输入高电平

  digitalWrite (IBpin, LOW); //IB口输入低电平 风扇转动

  delay(delaytime);//delay

  }
  
  else//距离大于三十厘米
  {
  
  flag=0;

    if(lastflag!=flag)//风扇状态改变
  {
    
    Serial.println("风扇关闭！！！");
    
    lastflag=0;
  
  }
  
  digitalWrite (IApin, HIGH); //同时输出高电平
    
  digitalWrite (IBpin, HIGH); //马达停转

  delay(delaytime);//delay
    
    }
    
    }
else///按钮为偶数次时
{
  
  digitalWrite(ledPin, LOW);

  digitalWrite (IApin, HIGH); 
    
  digitalWrite (IBpin, HIGH); 
  
  }
 
}
