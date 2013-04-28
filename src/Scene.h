#include <vector>
#include <glm\glm.hpp>
#include "GraphicObject.h"

class Scene{
private:
	int frameWidth, frameHeight;
	unsigned char* frame;
	Transform inputTransform;
	GraphicObject* currentGraphicObject;
	GraphicObject::Mode graphicObjectMode;
	std::vector<GraphicObject*> graphicObjects;

public:
	Scene(int frameWidth, int frameHeight);
	
	void add(GraphicObject* graphicObject);
	GraphicObject* getCurrentGraphicObject();
	void setCurrentGraphicObjectMode(GraphicObject::Mode mode);

	Transform getInputTransform();
	void setInputTransform(Transform t);

	void drawAllGraphicObjects();
	void drawGraphicObject(GraphicObject* graphicObject);
	void clearGraphicObjects();

	unsigned char* getFrame();
	void setFrame(unsigned char* newframe);
	void clearFrame();

	int getFrameHeight(){ return this->frameHeight;}
	int getFrameWidth(){ return this->frameWidth;}
	
	void loadFrame(char* location);
	void saveFrame(char* location);
};