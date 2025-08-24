struct Color {
  unsigned char R;
  unsigned char G;
  unsigned char B;

  static Color from_hue(double hue);
  Color scale(double value) const;
};
