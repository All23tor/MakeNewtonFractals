struct Color {
  unsigned char R;
  unsigned char G;
  unsigned char B;

  Color(); // Defaults to black
  Color(unsigned char r, unsigned char g,
        unsigned char b);    // Initializes RGB values (0-255)
  Color(double hue);         // Pick by hue [0, 360)
  Color scale(double value); // Returns copy of color scaled by decimal value
  unsigned int toUInt();     // Returns the pointer that the RGBA stores
};
