void intro() {
  display.clearDisplay(); 
  display.drawBitmap(32, 0, frames[frame], 64, 64, 1); 
  //32 = X position for starting drawing
  //0 = Y position for starting drawing 
  // frames[frame] = Pointer to the bitmap data (stored as a byte array in PROGMEM).
  // 64 = Width of the bitmap image in pixel
  // 64 = Breadth of the bitmap image in pixel
  // 1 = color to be used for drawing the bitmap image, 1 = black, 0 = white
  display.display(); 
  frame = (frame + 1) % FRAME_COUNT; 
}