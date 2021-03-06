#include <glm\glm.hpp>
#include <set>

#include "Primitives2D/Polygon2D.h"
#include "Splines/Line.h"
#include "Scene.h"
#include "Color.h"

extern int width, height;

Polygon2D::Polygon2D(){}

Polygon2D::Polygon2D(std::vector<glm::vec2> points, Color color)
: color(color) {
	this->vertices = points;
}

GraphicObject* Polygon2D::copy() const {
    return new Polygon2D(*this);
}


void Polygon2D::addPoint(int x, int y){
	this->vertices.push_back(glm::vec2(x,y));
	this->isCompleted = false;
}

void Polygon2D::draw(unsigned char* frame){
	std::set<float> intersectionPoints;
	glm::vec2 point1, point2;

	// find min and max y-values
	auto miny = vertices.at(0).y, maxy = vertices.at(0).y;
	for (glm::vec2& p : vertices){
		miny = std::min(miny, p.y);
		maxy = std::max(maxy, p.y);
	}
	
	// calculate intersections
	for (int yline = static_cast<int>(miny); yline < maxy; yline++){		// every line
		
		int lasty = 0;
		for (unsigned int i=0; i < vertices.size(); i++) {				// looking through every vertice
			

			if ( i == vertices.size()-1)
				point1 = vertices.at(i), point2 = vertices.at(0);
			else
				point1 = vertices.at(i), point2 = vertices.at(i+1);

			if ((point1.y >= yline && point2.y <= yline)
			|| (point1.y <= yline && point2.y >= yline)){
				float m = (point1.y - point2.y) / (point1.x - point2.x);				
				// y = m*(x + b1) + c1;  y = c2   =>  c2 = m*(x+b1) + c1  =>  x = (c2 - c1) / m + b1 
				float x = ((yline - point1.y) / m) + point1.x;
				intersectionPoints.insert(x);

				if ((point1.y == yline) && ((lasty > point1.y && point2.y > point1.y) || (lasty < point1.y && point2.y < point1.y)) ){
					intersectionPoints.insert(x + 0.001f);
				}
				lasty = static_cast<int>(point1.y);
			}
		}

		auto end = intersectionPoints.end();
		if (intersectionPoints.size() % 2 == 1)
			end = (--intersectionPoints.end());

		for (auto& p = intersectionPoints.begin(); p != end; p++){
			int xbegin = static_cast<int>(*p), xend = static_cast<int>(*(++p));
			for (int x = xbegin; x <= xend; x++)
				this->setPixel(x, yline, this->color, frame);
		}
		intersectionPoints.clear();
	}
}