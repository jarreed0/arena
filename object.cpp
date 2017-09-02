#include "object.h"

Object::Object() {

}

Object::~Object() {

}

void Object::setDest(int x, int y, int w, int h) {
	dest.x=x;
	dest.y=y;
	dest.w=w;
	dest.h=h;
}

void Object::setSource(int x, int y, int w, int h) {
	src.x=x;
	src.y=y;
	src.w=w;
	src.h=h;
}


void Object::setImage(string filename, SDL_Renderer* ren) {
	SDL_Surface* surf = IMG_Load(filename.c_str());
	tex = SDL_CreateTextureFromSurface(ren, surf);
	SDL_FreeSurface(surf);
}


void Object::setVelTo(Object o) {
	double angle = atan2(o.getDestY() - getDestY(), o.getDestX() - getDestX());
	double c = cos(angle) * getSpeed();
	double s = sin(angle) * getSpeed();
	setVelX(c);
	setVelY(s);
}

void Object::setVelTo(int x, int y) {
	double angle = atan2(y - getDestY(), x - getDestX());
	double c = cos(angle) * getSpeed();
	double s = sin(angle) * getSpeed();
	setVelX(c);
	setVelY(s);
}

void Object::lookAt(Object o) {
  double angle = atan2(o.getDestY() - getDestY(), o.getDestX() - getDestX()) * (180/PI);
  setAngle(angle);
}

void Object::lookAt(int x, int y) {
  double angle = atan2(y - getDestY(), x - getDestX()) * (180/PI);
  setAngle(angle);
}

bool Object::overlaps(Object b) {
  if ((getDestX() < (b.getDestX() + b.getDestW())) && ((getDestX() + getDestW()) > b.getDestX()) &&
   (getDestY() < (b.getDestY() + b.getDestH())) && ((getDestY() + getDestH()) > b.getDestY())) {
    return true;
  }
  else {
    return false;
  }
}

bool Object::overlaps(int x, int y, int w, int h) {
  if ((getDestX() < (x + w)) && ((getDestX() + getDestW()) > x) &&
   (getDestY() < (y + h)) && ((getDestY() + getDestH()) > y)) {
    return true;
  }
  else {
    return false;
  }
}

bool Object::contains(Object b)
{
    if (((b.getX() + b.getDestW()) < (getDestX() + getDestW())) && (b.getDestX() > getDestX()) &&
     (b.getDestY() > getDestY()) && ((b.getDestY() + b.getDestH()) < (getDestY() + getDestH()))) {
        return true;
    }
    else {
        return false;
    }
}

void Object::update() {
	fcount++;
	setSource(frame * src.w, 0, src.w, src.h);
	if(fcount >= framedelay) {
		fcount = 0;
		frame++;
		if(frame >= frames){
			if(dontcycle) setAlive(false);
			frame = 0;
		}
	}
	
	if(attackrate > 0) {
		acount++;
		if(acount >= attackrate) {
			acount = 0;
			attackready = true;
		}
	}
}