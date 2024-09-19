#pragma once
#include <raylib.h>

typedef struct Label {
  char *text;
  int fontSize;
  Vector2 position;
  Color color;
  int width;

  bool centerX;
  bool centerY;
} Label;

Label *CreateLabel(const char *text, Vector2 position, int fontSize,
                   Color color, bool centerX, bool centerY);
Label *CloneLabel(Label *label);
void FreeLabel(Label *label);
void RenderLabel(Label *label);
void SetLabelText(Label *label, const char *newText);
