#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 4 //định nghĩa chân
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);
String tag;
#include <string.h> // độ dài mảng kí tự
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

#include <HardwareSerial.h>
HardwareSerial mySoftwareSerial(1);
#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
DFRobotDFPlayerMini myDFPlayer;

const char *ssid = "iPhone";
const char *password = "23456789";
WiFiServer server(80);
String header; // dùng để gửi thông tin HTTP header về cho máy.
String ledState = "OFF";
#define RL1 2
#define RL2 0
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
int Coi = 32;
int cb1 = 39;
int cb2 = 34;
int cb3 = 35;
int cb6 = 15; // khi đến bước nhận diện mặt
int cb7 = 36; // khi ống vào trong cùng
int a1 = 1, a2 = 1, a3 = 1;
int dem = 0, l = 0;
int m = 0;
int n = 0;
int q = 0;
int r = 0;
int s = 0;
int t = 0;
int u = 0;
int v = 0;
int w;
int y;
int a;
int b;
int c;
int d;
int e;
int f;
int x;
int g = 0;
int h = 0;
int k = 0;
int o = 0;
int z = 0;
int p = 0;
int value = 0;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
      SPI.begin(); // Kích hoạt cổng truyền thông giao tiếp SPI
      mfrc522.PCD_Init();
      mlx.begin();
      pinMode(Coi, OUTPUT);
      digitalWrite(Coi, HIGH);
      mySoftwareSerial.begin(9600, SERIAL_8N1, 16, 17);
      if (!myDFPlayer.begin(mySoftwareSerial, true, false))
      {
            while (true)
            {
                  delay(0);
            }
      }
      myDFPlayer.volume(15);
      Serial.begin(115200);
      pinMode(cb1, INPUT);
      pinMode(cb2, INPUT);
      pinMode(cb3, INPUT);
      pinMode(cb6, OUTPUT);
      pinMode(13, OUTPUT);
      pinMode(cb7, INPUT);
      pinMode(RL1, OUTPUT);
      pinMode(RL2, OUTPUT);
      digitalWrite(cb6, HIGH);
      digitalWrite(RL1, HIGH);
      digitalWrite(RL2, HIGH);

      lcd.begin();
      lcd.backlight();
      // Ket noi voi mang wifi
      Serial.print("Connecting to ");
      Serial.println(ssid);
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED)
      {
            delay(500);
            Serial.print(".");
      }
      Serial.println("");
      Serial.println("WiFi connected.");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP()); // In ra dia chi IP
      server.begin();
}

void sendRequest(int cb, String value)
{
      // Su dung lop WiFiClient de tao ket noi TCP
      WiFiClient client;
      HTTPClient http;
      http.begin(client, "http://192.168.1.142/Nodemcu_db_record_view/read_db.php");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String postData;
      switch (cb)
      {
      case 1:
            postData = "cb1=" + value;
            //      id = http.getString());
            //      Serial.println(id);
            break;
      case 2:
            postData = "cb2=" + value;
            //      + ",id=" + id;
            break;
      case 3:
            postData = "nhietdo=" + value;
            break;
      case 4:
            postData = "ten=" + value;
            Serial.println("Dang goi case 4");
            break;
      case 5:
            postData = "khautrang=" + value;
            Serial.println("Dang goi case 5");
            break;
      }

      int httpCode = http.POST(postData);
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
      http.end();
}

void loop()
{
      //  for(;;){
      int cb1Value = digitalRead(cb1);
      int cb2Value = digitalRead(cb2);
      int cb3Value = digitalRead(cb3);

      // I. KHI NGƯỜI VÀO
      if (cb1Value == 0 and a1 == 1 and dem < 1)
      {
            dem = dem + 1;
            lcd.clear();
            lcd.setCursor(7, 0);
            lcd.print("BUOC 1");
            lcd.setCursor(6, 1);
            lcd.print("VUI LONG");
            lcd.setCursor(4, 2);
            lcd.print("SAT KHUAN TAY");
            while (true)
            {
                  if (l == 1)
                        break;
                  l = l + 1;
                  myDFPlayer.play(2);
                  delay(1500);
            }
            sendRequest(1, "on");
      }

      // II. SÁT KHUẨN TAY.
      // TH1: Cho tay sát khuẩn trước
      if (digitalRead(cb1) == 0 and digitalRead(cb2) == 0 and a2 == 1 and dem < 2)
      {
            dem = dem + 1;
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("BAN  DANG SAT  KHUAN");
            digitalWrite(RL1, LOW);
            while (true)
            {
                  if (m == 1)
                        break;
                  m = m + 1;
                  myDFPlayerfi`.play(3);
                  delay(1500);
            }
            delay(1000);
            digitalWrite(RL1, HIGH);
            lcd.clear();
            lcd.setCursor(7, 0);
            lcd.print("BUOC 2");
            lcd.setCursor(2, 1);
            lcd.print("BAN DA SAT KHUAN");
            lcd.setCursor(0, 2);
            lcd.print("DE TRAN  CACH MAY DO");
            lcd.setCursor(3, 3);
            lcd.print("THAN NHIET 2CM");
            while (true)
            {
                  if (n == 1)
                        break;
                  n = n + 1;
                  myDFPlayer.play(4);
                  delay(3500);
            }
            sendRequest(2, "OK SK");
            a = 1;
      }
      // TH2: Chạm tóc trước khi sát khuẩn.
      if (digitalRead(cb1) == 0 and digitalRead(cb3) == 0)
      {
            b = 1;
      }

      // III. ĐO THÂN NHIỆT.
      if (digitalRead(cb1) == 0 and a == 1 and b == 1 and dem < 3)
      {
            dem = dem + 1;
            lcd.clear();
            lcd.setCursor(3, 1);
            lcd.print("BAN  DANG  DO");
            lcd.setCursor(4, 2);
            lcd.print("THAN  NHIET");
            while (true)
            {
                  if (q == 1)
                        break;
                  q = q + 1;
                  myDFPlayer.play(5);
                  delay(2500);
            }
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("NHIET DO CUA BAN LA:");
            while (true)
            {
                  if (r == 1)
                        break;
                  r = r + 1;
                  myDFPlayer.play(7);
                  delay(2000);
            }
            float nhietdo;
            float temp_amb;
            temp_amb = mlx.readAmbientTempC();
            nhietdo = mlx.readObjectTempC();
            nhietdo = nhietdo + 2.6;
            lcd.setCursor(8, 1);
            lcd.print(nhietdo);
            char nd[50];
            sprintf(nd, "%0.2f", nhietdo);
            sendRequest(3, nd);
            if (nhietdo >= 37.5)
            {
                  lcd.setCursor(1, 2);
                  lcd.print("NHIET DO KHONG DAT");
                  lcd.setCursor(6, 3);
                  lcd.print("YEU CAU");
                  digitalWrite(Coi, LOW);
                  delay(2000);
                  lcd.clear();
                  lcd.setCursor(1, 0);
                  lcd.print("BAN KHONG THE VAO");
                  lcd.setCursor(2, 1);
                  lcd.print("CONG TY LUC NAY");
                  lcd.setCursor(0, 2);
                  lcd.print("VUI LONG  NHUONG CHO");
                  lcd.setCursor(3, 3);
                  lcd.print("CHO NGUOI KHAC");
                  digitalWrite(Coi, LOW);
                  while (true)
                  {
                        if (s == 1)
                              break;
                        s = s + 1;
                        myDFPlayer.play(1);
                        delay(3500);
                  }
            } // 6
            else
            {
                  lcd.setCursor(0, 2);
                  lcd.print("NHIET DO DAT YEU CAU");
                  digitalWrite(cb6, LOW);
                  while (true)
                  {
                        if (t == 1)
                              break;
                        t = t + 1;
                        myDFPlayer.play(8);
                        delay(1500);
                  }
                  c = 1;
            }
      }

      // IV. NHẬN DIỆN KHUÔN MẶT 1
      if (digitalRead(cb1) == 0 and digitalRead(cb7) == LOW and c == 1 and dem < 4)
      {
            dem = dem + 1;
            lcd.clear();
            lcd.setCursor(7, 0);
            lcd.print("BUOC 3");
            lcd.setCursor(2, 1);
            lcd.print("BO KHAU TRANG DE");
            lcd.setCursor(0, 2);
            lcd.print("NHAN DIEN  KHUON MAT");
            lcd.setCursor(2, 3);
            lcd.print("HOAC QUET THE TU");
            while (true)
            {
                  if (u == 1)
                        break;
                  u = u + 1;
                  myDFPlayer.play(6);
                  delay(1500);
            }
            v = 1;
      }

      // 0. PYTHON.
      {
            while (Serial.available())
            {
                  value = Serial.read();
            }
            if (digitalRead(cb1) == 0 and v == 1)
            {
                  if (value == '0')
                  {
                        k = 0;
                        p = 0;
                  }
                  if (value == '1' or value == '3')
                  {
                        k = k + 1;
                        delay(500);
                  }
                  if (value == '2' or value == '3')
                  {
                        p = p + 1;
                        delay(500);
                  }
                  if (k > 10)
                  {
                        g = 1;
                  }
                  if (p > 10)
                  {
                        h = 1;
                  }
            }

            if (digitalRead(cb1) == 0 and y == 1)
            {
                  if (value == '3')
                  {
                        x = x + 1;
                        delay(500);
                  }
                  if (x > 20)
                  {
                        o = 1;
                  }
                  if (value == '4')
                  {
                        x = 0;
                  }
            }
      }

      // IV. HIỆN THỊ TÊN NHÂN VIÊN.
      if (digitalRead(cb1) == 0 and g == 1 and dem < 5)
      {
            dem = dem + 1;
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("NGUYEN XUAN LOC");
            lcd.setCursor(7, 1);
            lcd.print("BUOC 4");
            lcd.setCursor(3, 2);
            lcd.print("DEO KHAU TRANG");
            lcd.setCursor(3, 3);
            lcd.print("DE VAO CONG TY");
            y = 1;
            sendRequest(4, "NGUYEN XUAN LOC");
      }
      if (digitalRead(cb1) == 0 and h == 1 and dem < 5)
      {
            dem = dem + 1;
            lcd.clear();
            lcd.setCursor(1, 0);
            lcd.print("NGUYEN TRUNG HIEU");
            lcd.setCursor(7, 1);
            lcd.print("BUOC 4");
            lcd.setCursor(3, 2);
            lcd.print("DEO KHAU TRANG");
            lcd.setCursor(3, 3);
            lcd.print("DE VAO CONG TY");
            y = 1;
            sendRequest(4, "NGUYEN TRUNG HIEU");
      }

      // V. THẺ TỪ.
      if (digitalRead(cb1) == 0 and v == 1)
      {
            thetu();
      }

      // VI. HIỆN THỊ ĐÃ ĐEO KHẨU TRANG.
      if (digitalRead(cb1) == 0 and o == 1 and dem < 6)
      {
            dem = dem + 1;
            lcd.clear();
            lcd.setCursor(1, 1);
            lcd.print("DA DEO  KHAU TRANG");
            lcd.setCursor(0, 2);
            lcd.print("MOI BAN  VAO CONG TY");
            digitalWrite(RL2, LOW);
            delay(3000);
            digitalWrite(RL2, HIGH);
            sendRequest(5, "OK KT");
      }

      // X. KHI NGƯỜI RA
      if (digitalRead(cb1) == 1)
      {
            digitalWrite(RL1, HIGH);
            digitalWrite(RL2, HIGH);
            digitalWrite(cb6, HIGH);
            digitalWrite(Coi, HIGH);
            dem = 0;
            a = b = c = d = e = f = l = m = n = q = r = s = t = u = v = w = x = y = g = h = k = p = o = z = 0;
            lcd.clear();
      }

      a1 = cb1Value;
      a2 = cb2Value;
      a3 = cb3Value;
}

void thetu()
{
      if (!mfrc522.PICC_IsNewCardPresent())
            return;
      if (mfrc522.PICC_ReadCardSerial())
      {
            for (byte i = 0; i < 4; i++)
            {
                  tag += mfrc522.uid.uidByte[i];
            }
            Serial.println(tag);

            if (tag == "2432542445")
            {
                  lcd.clear();
                  lcd.setCursor(4, 0);
                  lcd.print("KHACH HANG 1");
                  lcd.setCursor(7, 1);
                  lcd.print("BUOC 4");
                  lcd.setCursor(3, 2);
                  lcd.print("DEO KHAU TRANG");
                  lcd.setCursor(3, 3);
                  lcd.print("DE VAO CONG TY");
                  y = 1;
                  sendRequest(4, "KHACH HANG 1");
            }

            else if (tag == "146374228")
            {
                  lcd.clear();
                  lcd.setCursor(4, 0);
                  lcd.print("KHACH HANG 2");
                  lcd.setCursor(7, 1);
                  lcd.print("BUOC 4");
                  lcd.setCursor(3, 2);
                  lcd.print("DEO KHAU TRANG");
                  lcd.setCursor(3, 3);
                  lcd.print("DE VAO CONG TY");
                  y = 1;
                  sendRequest(4, "KHACH HANG 2");
            }

            else
            {
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("KHONG LA  KHACH HANG");
                  lcd.setCursor(1, 1);
                  lcd.print("KO THE VAO CONG TY");
                  lcd.setCursor(2, 2);
                  lcd.print("MOI BAN RA NGOAI");
                  digitalWrite(Coi, LOW);
                  sendRequest(4, "NOT KH");
            }

            tag = "";
            mfrc522.PICC_HaltA();
            mfrc522.PCD_StopCrypto1();
      }
}
