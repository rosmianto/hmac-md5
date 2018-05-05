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

void loop() {

}

void hmac_md5(byte key[], int keyLength, byte msg[], int msgLength, byte result[]) {

	int blockSize = 64;
	byte baKey[64] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	byte hash_result[16];
	byte baOuterKeyPadded[blockSize];
	byte baInnerKeyPadded[blockSize];
	byte tempHash[16];
	MD5Builder md5;

	if(keyLength > blockSize) {
		md5.begin();
		md5.add(key, keyLength);
		md5.calculate();
		md5.getBytes(baKey);
	}
	else {
		for(int i = 0; i < keyLength; i++) {
			baKey[i] = key[i];
		}
	}

	for (int i = 0; i < blockSize; i++) {
		baOuterKeyPadded[i] = baKey[i] ^ 0x5C;
		baInnerKeyPadded[i] = baKey[i] ^ 0x36;
	}

	// return hash(o_key_pad ∥ hash(i_key_pad ∥ message)) // Where ∥ is concatenation
	md5.begin();
	md5.add(baInnerKeyPadded, blockSize);
	md5.add(msg, msgLength);
	md5.calculate();
	md5.getBytes(tempHash);

	md5.begin();
	md5.add(baOuterKeyPadded, blockSize);
	md5.add(tempHash, 16);
	md5.calculate();
	md5.getBytes(hash_result);

	memcpy(result, hash_result, 16);
}