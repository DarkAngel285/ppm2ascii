#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char *gray_scale = " .:-=+*%@#";

int get_brightness(unsigned char r, unsigned char g, unsigned char b) {
  return (int)(0.299 * r + 0.587 * g + 0.114 * b);
}

void read_ppm(const char *filename, unsigned char **pixels, int *width,
              int *height, int *max_value) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    perror("Error opening file");
    exit(1);
  }
  char header[3];
  fscanf(file, "%2s\n", header);
  if (header[0] != 'P' || header[1] != '6') {
    printf("Error invalid filetype\n");
    exit(1);
  }
  fscanf(file, "%d %d\n", width, height);
  fscanf(file, "%d\n", max_value);
  *pixels = (unsigned char *)malloc(*width * *height * 3);
  if (*pixels == NULL) {
    printf("Pixel memory allocation error\n");
    exit(1);
  }
  fread(*pixels, 3, *width * *height, file);
  fclose(file);
}

void image_to_ascii(const unsigned char *pixels, int width, int height,
                    int max_value) {
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      int idx = (y * width + x) * 3;
      unsigned char r = pixels[idx];
      unsigned char g = pixels[idx + 1];
      unsigned char b = pixels[idx + 2];
      int brightness = get_brightness(r, g, b);
      int gray_idx = brightness * strlen(gray_scale) / max_value;
      for (int i = 0; i < 3; ++i)
        printf("%c", gray_scale[gray_idx]);
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Invalid arguments\n");
    exit(1);
  }
  const char *filename = argv[1];
  unsigned char *pixels;
  int width, height, max_value;
  read_ppm(filename, &pixels, &width, &height, &max_value);
  image_to_ascii(pixels, width, height, max_value);
  free(pixels);
  return 0;
}
