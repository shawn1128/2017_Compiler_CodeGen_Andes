int main() {
  int a = 5000;
  int b = 5000;

  //b = a / 3 + b * 3 - b;

  digitalWrite(13, HIGH);
  delay(a);
  digitalWrite(13, LOW);
  delay(b);

  return 0;
}