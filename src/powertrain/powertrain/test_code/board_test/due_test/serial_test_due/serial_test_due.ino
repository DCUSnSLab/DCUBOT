void setup() {
    Serial.begin(9600);
    while(!Serial) {
        ;
    }
}

void loop() {
    Serial.write("Hi");
    String data = Serial.readString();
    Serial.println(data);
    delay(1000);
}