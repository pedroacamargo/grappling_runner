#include "../includes/colors.hpp"

Color LessOpacity(Color color, float opacity) {
  return (Color){color.r, color.g, color.b, (unsigned char) opacity};
}