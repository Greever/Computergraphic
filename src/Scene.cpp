
class Spline;
#include "Scene.h"
#include "gl/glew.h"
#include "Files/PPMFile.h"
#include "Splines/Line.h"
#include "Splines/Circle.h"
#include "Splines/BezierCurve.h"
#include "Splines/BSpline.h"
#include "Primitives2D/Triangle2D.h"


Scene::Scene(int frameWidth, int frameHeight)
{
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
	this->frame = new unsigned char[frameWidth * frameHeight * 3];
	this->graphicObjects = std::vector<GraphicObject*>();
	this->graphicObjectMode = GraphicObject::Mode::TRIANGLE;
	this->currentGraphicObject = NULL;
}

void Scene::add(GraphicObject* graphicObject)
{
	bool alreadyExists = false;
	for (auto go = this->graphicObjects.begin(); go != this->graphicObjects.end(); go++)
		if (graphicObject == *go)
			alreadyExists = true;
	if (!alreadyExists)
		this->graphicObjects.push_back(graphicObject);
}

GraphicObject* Scene::getCurrentGraphicObject(){
	if (this->currentGraphicObject == NULL
	 || this->currentGraphicObject->isCompleted){
		GraphicObject* go;
		switch (this->graphicObjectMode){
			case GraphicObject::Mode::LINE:{
				go = new Line();
				break;
			}
			case GraphicObject::Mode::CIRCLE:{
				go = new Circle();
				break;
			}
			case GraphicObject::Mode::BEZIER:{
				go = new BezierCurve();
				break;
			}
			case GraphicObject::Mode::BSPLINE:{
				go = new BSpline();
				break;
			}
			case GraphicObject::Mode::TRIANGLE:{
				go = new Triangle2D();
				break;
			}
			default:{
				go = NULL;
				break;
			}
		}
		currentGraphicObject = go;
	}
	return this->currentGraphicObject;
}

void Scene::drawAllGraphicObjects()
{
	for (unsigned int i=0; i < graphicObjects.size(); i++)
		drawGraphicObject(graphicObjects.at(i));
}

void Scene::drawGraphicObject(GraphicObject* graphicObject)
{
	graphicObject->draw(this->frame);
}

unsigned char* Scene::getFrame()
{
	return this->frame;
}

void Scene::clearFrame(){
	for (int i=0; i < this->frameWidth * this->frameHeight * 3; i++) 
		this->frame[i] = 0;
}

void Scene::setFrame(unsigned char* newframe)
{
	this->frame = newframe;
}

void Scene::saveFrame(char* location)
{
	PPMFile::savePPM(location, this->frame, this->frameWidth, this->frameHeight);
}

void Scene::loadFrame(char* location)
{
	PPMFile::readPPM(fopen( location, "r"), new GLsizei(this->frameWidth), new GLsizei(this->frameHeight));
}