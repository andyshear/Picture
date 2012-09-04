#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class PictureApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

private:
	Surface* mySurface_;
	Surface my_pic;

	static const int width = 800;
	static const int height = 600;
	static const int size = 1024;

	uint8_t* my_blur_pattern_;

	void drawRectangle (int xPos, int yPos, int width, int height, uint8_t* pixels, Color8u c);
	void drawCircle (int xPos, int yPos, int radius, uint8_t* pixels, Color8u c);
	void drawLine (int xPos, int yPos, int xPos2, int yPos2, int length, uint8_t* pixels, Color8u c);
	void drawTriangle (int xPos, int yPos, int length, uint8_t* pixels, Color8u c);	
	void blur(uint8_t* image, uint8_t* pattern);
	
};

void PictureApp::drawRectangle (int xPos, int yPos, int w, int h, uint8_t* pixels, Color8u c){
	int x;
	int y;
	int offset;
	for(y=yPos; y<h; y++){
		for(x=xPos; x<w; x++){
			offset = 3*(x + y*size);
			pixels[offset] =  c.r;
			pixels[offset+1] = c.g;
			pixels[offset+2] = c.b;
		}
	}
}

void PictureApp::drawTriangle (int x, int y, int length, uint8_t* pixels, Color8u c){
	
	int offset;
	
	for(int z = 0; z<length; z++){
		offset = 3*(x + y*size);
		pixels[offset] =  c.r;
		pixels[offset+1] = c.g;
		pixels[offset+2] = c.b;
		
		x+=1;
		y+=1;
	}
	for(int z = 0; z<length*2; z++){
		offset = 3*(x + y*size);
		pixels[offset] =  c.r;
		pixels[offset+1] = c.g;
		pixels[offset+2] = c.b;
		
		x-=1;		
	}
	for(int z = 0; z<length; z++){
		offset = 3*(x + y*size);
		pixels[offset] =  c.r;
		pixels[offset+1] = c.g;
		pixels[offset+2] = c.b;
		
		x+=1;
		y-=1;
	}
}

void PictureApp:: blur(uint8_t* image, uint8_t* pattern){
	
}

void PictureApp::setup()
{
	mySurface_ = new Surface(size, size, false);

	Surface my_pic(loadImage( loadResource(RES_PICTURE) ));
	uint8_t* blur_data = my_pic.getData();
	my_blur_pattern_ = new uint8_t[width*height*3];
	for(int y=0; y<height; y++){
		for(int x=0; x<width; x++){
			int offset = 3*(x + y*width);
			my_blur_pattern_[offset] = blur_data[offset];
		}
	}
}

void PictureApp::mouseDown( MouseEvent event )
{
}

void PictureApp::update()
{
	uint8_t* dataArray = (*mySurface_).getData();
	

	drawRectangle(0,20,200,200,dataArray, Color8u(255,100,10));
	drawTriangle(200,200,50,dataArray,Color8u(10,20,255));
	blur(dataArray, my_blur_pattern_);
}

void PictureApp::draw()
{	
	gl::draw(*mySurface_); 
}

CINDER_APP_BASIC( PictureApp, RendererGl )
