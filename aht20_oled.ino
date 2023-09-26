// load AHT20 libraries
#include <Wire.h>
#include <AHT20.h>

// load OLED libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// initialize components
AHT20 aht20;
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

void setup()
{
  // AHT20 Init
  Serial.begin(115200);

  Wire.begin();
  if (aht20.begin() == false)
  {
    Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    while (1);
  }
  Serial.println("AHT20 acknowledged.");

  // OLED Init
  delay(250); // wait for the OLED to power up
  display.begin(0x3C, true); // Address 0x3C default

  // Setup display
  display.clearDisplay();
  display.display();

  display.setRotation(1);

  // Display test
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
}

void loop()
{
  if (aht20.available() == true)
  {
    //Get the new temperature and humidity value
    float temperature = aht20.getTemperature();
    float humidity = aht20.getHumidity();

    //Print the results
    Serial.print("Temperature: ");
    Serial.print(temperature, 2);
    Serial.print(" C\t");
    Serial.print("Humidity: ");
    Serial.print(humidity, 2);
    Serial.print("% RH");

    Serial.println();

    float temperatureF = (temperature * (9.0 / 5.0)) + 32.0;

    float roundedTemp = ((float)floor(temperatureF * 10.0)) / 10.0;
    float roundedHumidity = ((float)floor(humidity * 10.0)) / 10.0;

    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Temp: " + String(roundTemp, 1) + " *F ");
    // lcd.setCursor(0, 1);
    // lcd.print("Humi: " + String(floor(humidity), 1) + "% ");
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Temp:");
    display.println(String(roundedTemp, 1) + " *F ");
    display.println("Humidity:");
    display.println(String(floor(roundedHumidity), 1) + "% ");
    display.display(); // actually display all of the above
  }

  //The AHT20 can respond with a reading every ~50ms. However, increased read time can cause the IC to heat around 1.0C above ambient.
  //The datasheet recommends reading every 2 seconds.
  delay(2000);
}