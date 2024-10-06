// #include <WiFi.h>
// #include <WebSocketsServer.h>

// const char* ssid = "ConnectValue_A401_2G";
// const char* password = "CVA401!@#$";

// WebSocketsServer webSocket = WebSocketsServer(81);

// void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
//   switch(type) {
//     case WStype_DISCONNECTED:
//       Serial.printf("[%u] Disconnected!\n", num);
//       break;
//     case WStype_CONNECTED:
//       {
//         IPAddress ip = webSocket.remoteIP(num);
//         Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
//         webSocket.sendTXT(num, "Connected");
//       }
//       break;
//     case WStype_TEXT:
//       Serial.printf("[%u] Text: %s\n", num, payload);
//       webSocket.sendTXT(num, "Message received");
//       break;
//   }
// }

// void setup() {
//   Serial.begin(115200);
  
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to WiFi...");
//   }
  
//   Serial.print("Connected to WiFi with IP: ");
//   Serial.println(WiFi.localIP());  // IP 주소 출력

//   webSocket.begin();
//   webSocket.onEvent(webSocketEvent);

// }

// void loop() {
//     webSocket.loop();
// }

// #include <Wire.h>
// #include <MPU6050.h>
// #include <WiFi.h>
// #include <WebSocketsServer.h>

// const char* ssid = "ConnectValue_A401_2G";
// const char* password = "CVA401!@#$";

// WebSocketsServer webSocket = WebSocketsServer(81);
// MPU6050 mpu;

// void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
//   // 클라이언트와의 이벤트 처리
// }

// void setup() {
//   Serial.begin(115200);
//   Wire.begin();
//   mpu.initialize();

//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to WiFi...");
//   }
//   Serial.println("Connected to WiFi");
//   Serial.print("Connected to WiFi with IP: ");
//   Serial.println(WiFi.localIP());  // IP 주소 출력
//   webSocket.begin();
//   webSocket.onEvent(webSocketEvent);
// }

// void loop() {
//   webSocket.loop();
  
//   int16_t ax, ay, az;
//   int16_t gx, gy, gz;
  
//   mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
//   String message = "Gyro: " + String(gx) + ", " + String(gy) + ", " + String(gz);
//   webSocket.broadcastTXT(message);
  
//   delay(500); // 0.5초마다 데이터 전송
// }

// #include <WiFi.h>
// #include <WebSocketsServer.h>

// const char* ssid = "ConnectValue_A401_2G";
// const char* password = "CVA401!@#$";

// WebSocketsServer webSocket = WebSocketsServer(81);

// void setup() {
//     Serial.begin(115200);
//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(1000);
//         Serial.println("Connecting to WiFi...");
//     }
//     Serial.println("Connected to WiFi");
//     Serial.print("IP Address: ");
//     Serial.println(WiFi.localIP());  // 연결된 IP 주소 출력
//     webSocket.begin();
//     webSocket.onEvent(webSocketEvent);
// }

// void loop() {
//     webSocket.loop();
//     // 자이로 센서 값을 읽고 웹소켓으로 전송
//     float gyroValue = readGyroSensor(); // 센서 값 읽기 함수
//     String message = String(gyroValue);
//     webSocket.broadcastTXT(message);
//     delay(100); // 주기적으로 전송
// }

// void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
//     // 클라이언트 이벤트 처리 (필요시)
// }

// float readGyroSensor() {
//     // 자이로 센서 값 읽는 코드 작성
//     return random(0, 100); // 임시 값 (예시)
// }

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <WiFi.h>
#include <WebSocketsServer.h>
Adafruit_MPU6050 mpu;

const char* ssid = "ConnectValue_A401_2G";
const char* password = "CVA401!@#$";

WebSocketsServer webSocket = WebSocketsServer(81);

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
        Serial.println("Connected to WiFi");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    }
    
   

    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10);
        }
    }
    
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}

void loop() {
    webSocket.loop();
    
    // 자이로 센서 값 읽기
    float gyroX, gyroY, gyroZ;
    readGyroSensor(gyroX, gyroY, gyroZ);
    
    String message = String("X: ") + String(gyroX, 2) + 
                     ", Y: " + String(gyroY, 2) + 
                     ", Z: " + String(gyroZ, 2);
    
    webSocket.broadcastTXT(message);
    delay(100); // 주기적으로 전송
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    // 클라이언트 이벤트 처리 (필요시)
}

void readGyroSensor(float &x, float &y, float &z) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    
    // 자이로 데이터 읽기
    x = g.gyro.x;
    y = g.gyro.y;
    z = g.gyro.z;
}

