#include <glm\glm.hpp>

#include "GraphicObject.h"
#include "Transform.h"
#include "Scene.h"
#include <memory>
#include "Splines\Line.h"
#include "Color.h"

extern int width, height;
extern std::unique_ptr<Scene> scene;

GraphicObject::GraphicObject(){
	this->transformMatrix = Transform();
}

GraphicObject* GraphicObject::operator* (Transform transform){
	std::vector<glm::vec2> newvertices;
	for (auto v : this->vertices)
		newvertices.push_back(transform * v);
	this->vertices = newvertices;
	return this;
}

void GraphicObject::setTransformationMatrix(Transform transform){
	this->transformMatrix = transform;
}

Transform GraphicObject::getTransformationMatrix(){
	return Transform(this->transformMatrix);
}

void GraphicObject::setPixel(int x, int y, Color color, unsigned char* frame) {
	if ((x>=0 && y>=0) && (x < width && y < height) ) {
		frame[(y * width + x) * 3 + 0] = color.getR();
		frame[(y * width + x) * 3 + 1] = color.getG();
		frame[(y * width + x) * 3 + 2] = color.getB();
	}
}

char* GraphicObject::toString(Mode mode){
	if (mode == Mode::LINE)
		return "Line";
	else if (mode == Mode::CIRCLE)
		return "Circle";
	else if (mode == Mode::BEZIER)
		return "Bezier";
	else if (mode == Mode::BSPLINE)
		return "BSpline";
	else if (mode == Mode::TRIANGLE)
		return "Triangle";
	else if (mode == Mode::RECTANGLE)
		return "Rectangle";
	else if (mode == Mode::POLYGON)
		return "Polygon";
	else
		return "Not known";
}

std::vector<glm::vec2> GraphicObject::getVertices(){
	return this->vertices;
}