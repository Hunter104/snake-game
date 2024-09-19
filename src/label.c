#include "label.h"
#include "memory_utils.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

Label *CreateLabel(const char *text, Vector2 position, int fontSize,
                   Color color, bool centerX, bool centerY) {
  Label *label = safeMalloc(sizeof *label);
  label->text = _strdup(text);
  label->fontSize = fontSize;
  label->position = position;
  label->color = color;
  label->width = MeasureText(label->text, label->fontSize);
  label->centerY = centerY;
  label->centerX = centerX;

  return label;
}

void FreeLabel(Label *label) {
  free(label->text);
  free(label);
}

Label *CloneLabel(Label *label) {
  char *newText = strdup(label->text);
  Label *newLabel = safeMalloc(sizeof *newLabel);
  *newLabel = *label;
  newLabel->text = newText;

  return newLabel;
}

void SetLabelText(Label *label, const char *newText) {
  free(label->text);
  label->text = strdup(newText);
  label->width = MeasureText(label->text, label->fontSize);
}

void RenderLabel(Label *label) {
  float positionX = !label->centerX ? label->position.x
                                    : label->position.x - label->width / 2;
  float positionY = !label->centerY
                        ? label->position.y
                        : label->position.y - (float)label->fontSize / 2;
  DrawText(label->text, (int) positionX, (int) positionY, label->fontSize, label->color);
}
