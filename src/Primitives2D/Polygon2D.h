#pragma once
#include <vector>

#include "Primitive2D.h"
#include "Color.h"

class Polygon2D : public Primitive2D{
private:
	std::vector<glm::vec2> points; 
	Color color;

public:
	Polygon2D(std::vector<glm::vec2> points, Color color);

	void addPoint(int x, int y);
	void draw(unsigned char* frame);
};