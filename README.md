# HMAC-MD5
This is an HMAC-MD5 library implementation for ESP8266 on Arduino IDE. This library uses MD5 64-byte blocksize, and 
16-byte hash result.

# Usage
```cpp
byte msg[] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
byte key[] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };

byte result[16];

void setup() {
	Serial.begin(115200);
	Serial.println("HMAC-MD5 Test");
	hmac_md5(key, sizeof(key), msg, sizeof(msg), result);

	// -------------- DEBUGGING PURPOSE ------------------
	for(int i = 0; i < 16; i++) {
		byte b = result[i];
		if(b < 0x10) Serial.print('0');
		Serial.print(b, HEX); Serial.print(' ');
	}
	// -------------- DEBUGGING PURPOSE ------------------
}
```

# Author
Rosmianto A. Saputro

This library is licensed under MIT License.

You are free (as in freedom) to use this library as long you attribute this library to me. I'm holding no liability for any damages that may caused by using this library.
