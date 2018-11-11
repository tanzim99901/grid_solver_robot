void sonar_test()
{
  Serial.println(digitalRead(sonar_pin));
  if (digitalRead(sonar_pin))
  {
    digitalWrite(LED_blue, HIGH);
  }
  else digitalWrite(LED_blue, LOW);
}

