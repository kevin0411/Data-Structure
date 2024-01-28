#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;
  alma.readFromFile("../data/alma.png");
  Image i;
  i.readFromFile("../data/i.png");
  Image pen1, pen2;
  pen1.readFromFile("../data/penguin.png");
  pen2.readFromFile("../data/penguin.png");
  StickerSheet s = StickerSheet(alma,4);
  s.addSticker(i,0,0);
  s.addSticker(pen1, 100,100);
  s.addSticker(pen2, 200,200);
  Image output = s.render();
  output.writeToFile("../data/myImage.png");

  return 0;
}
