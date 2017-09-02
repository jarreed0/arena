#ifndef OBJECT_H
#define OBJECT_H
#define PI 3.14159265358979323846

#include <iostream>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <math.h>

class Object {
  public:
	Object();
	~Object();
	SDL_Rect getDest() const {return dest;}
	SDL_Rect getSource() const {return src;}
	void setDest(int x, int y, int w, int h);
	void setSource(int x, int y, int w, int h);
	void setImage(string filename, SDL_Renderer* ren);
	SDL_Texture* getTex() const {return tex;}
	int getX() {return x;}
	int getY() {return y;}
	int getDestX() {return dest.x;}
	int getDestY() {return dest.y;}
	int getDestW() {return dest.w;}
	int getDestH() {return dest.h;}
	double getVelX() {return velX;}
	double getVelY() {return velY;}
	double getSpeed() {return speed;}
	double getAngle() {return angle;}
	bool isAlive() {return alive;}
	int getFrame() {return frame;}
	int getFrames() {return frames;}
	void setFrames(int f) {frames = f;}
	void setFrameDelay(int d) {framedelay = d;}
	void setX(int x1) {x = x1;}
	void setY(int y1) {y = y1;}
	void setDestX(int x1) {dest.x = x1;}
	void setDestY(int y1) {dest.y = y1;}
	void setVelX(double vx) {velX = vx;}
	void setVelY(double vy) {velY = vy;}
	void setSpeed(double s) {speed = s;}
	void setAngle(double a) {angle = a;}
	void setVelTo(Object o);
	void setVelTo(int x, int y);
	bool overlaps(Object b);
	bool overlaps(int x, int y, int w, int h);
	bool contains(Object b);
	void lookAt(Object o);
	void lookAt(int x, int y);
	void update();
	void setAlive(bool b) {alive = b;SDL_DestroyTexture(tex);}
	void setYOffset(int y) {yoffset = y;}
	int getYOffset() {return yoffset;}
	void setXOffset(int xo) {xoffset = xo;}
	int getXOffset() {return xoffset;}
	void setAttackRate(int ar) {attackrate = ar;}
	int getAttackRate() {return attackrate;}
	void setHealth(int h) {health = h;}
	int getHealth() {return health;}
	void stopFrameCycle(bool c) {dontcycle = c;}
	bool attackReady() {return attackready;}
	void justAttacked() {attackready = false;}
	void setId(int i) {id = i;}
	int getId() {return id;}
	bool isDisplayable() {return displayable;}
	void setDisplayable(bool d) {displayable = d;}
	private:
	SDL_Rect dest;
	SDL_Rect src;
	SDL_Texture* tex;
	int x, y, id, frames = 0, frame = 0, framedelay = 10, fcount = 0, xoffset = 0, yoffset = 0, attackrate = 0, acount = 0, health = 0;
	double velX, velY, speed, angle = 0;
	bool alive = true, dontcycle = false, attackready = false, displayable = true;
};

#endif //OBJECT_H