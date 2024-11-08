struct Color {
  unsigned char R;
  unsigned char G;
  unsigned char B;

  Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0);
  Color(double hue);
  Color scale(double value) const;
};
