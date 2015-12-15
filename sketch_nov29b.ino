#include <QueueList.h>

struct motor_tuple {
  unsigned long motor1;
  unsigned long motor2;
  unsigned long motor3;
  unsigned long motor4;
};

struct motor_run {
  int number;
  unsigned long startTime;
  int duration;
};

String line = "";
int motor1_pin = 9;
int motor2_pin = 10;
int motor3_pin = 11;
int motor4_pin = 5;
int motor5_pin = 6;

QueueList<motor_tuple> commandQueue;

QueueList<motor_run> motorQueue1;
QueueList<motor_run> motorQueue2;
QueueList<motor_run> motorQueue3;
QueueList<motor_run> motorQueue4;
QueueList<motor_run> motorQueue5;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting App...");
}

void check_queue() {
  
  if(motorQueue1.count() > 0) {
    Serial.println("found something in queue 1");
    motor_run m = motorQueue1.peek();
    if(m.startTime >= millis()) {
      analogWrite(motor1_pin, 255);
    } else if ((m.startTime + m.duration) >= millis()) {
      analogWrite(motor1_pin, 0);
      motorQueue1.pop();
    }
  }
  
  if(motorQueue2.count() > 0) {
    Serial.println("found something in queue 2");
    motor_run m = motorQueue2.peek();
    if(m.startTime > millis()) {
      analogWrite(motor2_pin, 255);
    } else if ((m.startTime + m.duration) >= millis()) {
      analogWrite(motor2_pin, 0);
      motorQueue2.pop();
    }
  }

  if(motorQueue3.count() > 0) {
    Serial.println("found something in queue 3");
    motor_run m = motorQueue3.peek();
    if(m.startTime > millis()) {
      analogWrite(motor3_pin, 255);
    } else if ((m.startTime + m.duration) >= millis()) {
      analogWrite(motor3_pin, 0);
      motorQueue3.pop();
    }
  }

  if(motorQueue4.count() > 0) {
    Serial.println("found something in queue 4");
    motor_run m = motorQueue4.peek();
    if(m.startTime > millis()) {
      analogWrite(motor4_pin, 255);
    } else if ((m.startTime + m.duration) >= millis()) {
      analogWrite(motor4_pin, 0);
      motorQueue4.pop();
    }
  }  
  
  if(motorQueue5.count() > 0) {
    Serial.println("found something in queue 5");
    motor_run m = motorQueue5.peek();
    if(m.startTime > millis()) {
      analogWrite(motor5_pin, 255);
    } else if ((m.startTime + m.duration) >= millis()) {
      analogWrite(motor5_pin, 0);
      motorQueue5.pop();
    }
  }
}

void loop() {
  unsigned long currentMillis = millis();
  
  check_queue();  
  
  if(Serial.available() > 0) {
    char mybyte = Serial.read();
    
    if(mybyte == 10) {
      // its a lf
      
      Serial.println("line: " + line);
      // 05002551000255100025510002551000255 05000001000000100000010000001000000 10002551000255100025510002551000255 20000002000000200000020000002000000  
      
      // debug only 
      if(line == "on") {
        analogWrite(motor1_pin, 255);
        analogWrite(motor2_pin, 255);
        analogWrite(motor3_pin, 255);
        analogWrite(motor4_pin, 255);
        analogWrite(motor5_pin, 255);
        return;
      }
      if(line == "off") {
        analogWrite(motor1_pin, 0);
        analogWrite(motor2_pin, 0);
        analogWrite(motor3_pin, 0);
        analogWrite(motor4_pin, 0);
        analogWrite(motor5_pin, 0);
        return;
      }
      if(line == "mid") {
        analogWrite(motor1_pin, 100);
        analogWrite(motor2_pin, 100);
        analogWrite(motor3_pin, 100);
        analogWrite(motor4_pin, 100);
        analogWrite(motor5_pin, 100);
        return;
      }

      /*
      int counter = 0;      
      while(true) {
        if(counter == 5) {
          return;
        }
        
        if(line.length()%35 == 0) {
         String block = line.substring(0, 34);
         line = line.substring(35, line.length());
         Serial.println("block: " + block);
         
         String motor1_str = block.substring(0,6);
         String motor2_str = block.substring(7, 13);
         String motor3_str = block.substring(14, 20);
         String motor4_str = block.substring(21, 27);
         String motor5_str = block.substring(28, 34);
         
         Serial.println("Motor1: " + motor1_str);
         Serial.println("Motor2: " + motor2_str);
         Serial.println("Motor3: " + motor3_str);
         Serial.println("Motor4: " + motor4_str);
         Serial.println("Motor4: " + motor5_str);
         
         int motor1_millis = motor1_str.substring(0, 3).toInt();
         int motor1_strength = motor1_str.substring(4, 6).toInt();
         
         int motor2_millis = motor2_str.substring(0, 3).toInt();
         int motor2_strength = motor2_str.substring(4, 6).toInt();
         
         int motor3_millis = motor3_str.substring(0, 3).toInt();
         int motor3_strength = motor3_str.substring(4, 6).toInt();
         
         int motor4_millis = motor4_str.substring(0, 3).toInt();
         int motor4_strength = motor4_str.substring(4, 6).toInt();
         
         int motor5_millis = motor5_str.substring(0, 3).toInt();
         int motor5_strength = motor5_str.substring(4, 6).toInt();

         if(line.length() == 0) {
           counter++;
           break;
         }
         
        } else {
          Serial.println("no motor code");
          break;
        }
      }
      */
      
      //commandQueue.push(line);
      
      unsigned long startTime = currentMillis + 100;
      
      int i = 0;
      while(line.length() > 0) {
        Serial.println("i = " + i);
        String seq = line.substring(0, 35);
        String motor1 = seq.substring(0, 6);
        String motor2 = seq.substring(7, 13);
        String motor3 = seq.substring(14, 20);
        String motor4 = seq.substring(21, 27);
        String motor5 = seq.substring(28, 34);
        
        if(i == 0) {
          Serial.println("pushing motor queue 1");
          motorQueue1.push(motor_run { 1, startTime, startTime + motor1.substring(0, 3).toInt() });
        }
        if(i == 1) {
          Serial.println("pushing motor queue 2");
          motorQueue2.push(motor_run { 2, startTime, startTime + motor2.substring(0, 3).toInt() });
        }
        if(i == 2) {
          Serial.println("pushing motor queue 3");
          motorQueue3.push(motor_run { 3, startTime, startTime + motor3.substring(0, 3).toInt() });
        }
        if(i == 3) {
          Serial.println("pushing motor queue 4");
          motorQueue4.push(motor_run { 4, startTime, startTime + motor4.substring(0, 3).toInt() });
        }
        if(i == 4) {
          Serial.println("pushing motor queue 5");
          motorQueue5.push(motor_run { 5, startTime, startTime + motor5.substring(0, 3).toInt() });
        }
        
        line = line.substring(40, line.length());
        i++;
        Serial.println("increment i");
      }
      
      line = "";
    } else {
      line += mybyte;
    }
      
  }
  
}
