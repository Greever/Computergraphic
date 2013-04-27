#pragma once

#include "Primitive2D.h"
#include "Color.h"

class Rectangle2D : public Primitive2D{
private:
	glm::vec2 firstPoint;
	glm::vec2 secondPoint;
	bool bayrzentricColor;
	Color color;

public:
	Rectangle2D(float firstPointX, float firstPointY, float secondPointX, float secondPointY, Color color = Color(), bool bayrzentricColor = false);
	Rectangle2D(glm::vec2 firstPoint, glm::vec2 secondPoint, Color color = Color(), bool bayrzentricColor = false);

	void addPoint(int x, int y);

	void draw(unsigned char* frame);
};