#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define CHAR_WIDTH 6

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
bool isClear = true;

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) Serial.println(F("fail"));
  display.display();
  display.clearDisplay();
  displayWelcomeText("PTIT");
  delay(2000);
  emptyDisplay();
}
void loop() {
  String input = readSerial();
  if (input != "") {
    displayText(input);
    display.clearDisplay();
  }
}

String readSerial() {
  return Serial.readStringUntil('\n');
}

void emptyDisplay() {
  isClear = true;
  display.clearDisplay();
  display.print("");
  display.display();
  display.clearDisplay();
}
void displayText(String text) {
  int maxLength = SCREEN_WIDTH / CHAR_WIDTH;
  int startPos = 0;
  while (startPos < text.length()) {
    int spacePos = text.lastIndexOf(' ', min(startPos + maxLength, text.length()));  // Tìm khoảng trắng gần nhất
    if (spacePos == -1) spacePos = min(startPos + maxLength, text.length());
    String subText = text.substring(startPos, spacePos);
    displaySubText(subText);
    delay(2000);
    display.clearDisplay();
    startPos = spacePos + 1;
  }
  if (!isClear) emptyDisplay();
}
void displayWelcomeText(String text) {
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);

  // Text center
  int xPos = (SCREEN_WIDTH - (text.length() * 12)) / 2;
  int yPos = (SCREEN_HEIGHT - 18) / 2;

  display.setCursor(xPos, yPos);
  display.print(text);
  display.display();
}
void displaySubText(String text) {
  isClear = false;
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Text center
  int xPos = (SCREEN_WIDTH - (text.length() * CHAR_WIDTH)) / 2;
  int yPos = (SCREEN_HEIGHT - CHAR_WIDTH) / 2;

  display.setCursor(xPos, yPos);
  display.print(text);
  display.display();
}
