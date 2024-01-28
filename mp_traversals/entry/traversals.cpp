
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "ImageTraversal.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {
  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png;       png.readFromFile("../data/gojo_bw.png");
  PNG new_img = png;
  // Traversals::ImageTraversal bfs1(png, Point(490, 590), 0.1, {
  //   Traversals::bfs_add, Traversals::bfs_pop, Traversals::bfs_peek
  // });

  Traversals::ImageTraversal bfs2(png, Point(490, 590), 0.1, {
    Traversals::bfs_add, Traversals::bfs_pop, Traversals::bfs_peek
  });

  Traversals::ImageTraversal bfs3(png, Point(380, 270), 0.1, {
    Traversals::bfs_add, Traversals::bfs_pop, Traversals::bfs_peek
  });

  MyColorPicker purple(1);
  MyColorPicker blue(0);
  FloodFilledImage image(png);
  // image.addFloodFill( bfs1, purple );
   image.addFloodFill( bfs2, purple );
  image.addFloodFill( bfs3, blue );

  Animation animation = image.animate(2000);
  PNG secondFrame = animation.getFrame(1);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  return 0;
  }
  
