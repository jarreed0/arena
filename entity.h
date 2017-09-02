#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "object.h"

class Entity : public Object {
public:
    Entity() {rev=0;alive=1;}
    void setHealth(int h) {health=h;}
    void setMaxHealth(int h) {maxHealth=h;}
    int getHealth() const {return health;}
    int getMaxHealth() const {return maxHealth;}
    int createCycle(int r, int w, int h, int amount, int speed);
    void setCurAnimation(int c) {begin=0;curAnim = c;}
    void updateAnimation();
    void reverse(bool r) {rev=r;}
    void reverse(bool r, int nA) {rev=r; nAb=1; nA=newAnim;}
    int getCurAnimation() const {return curAnim;}
    int getSpeed() const {return speed;}
    void setSpeed(int s) {speed=s;}
    int getGravity() const {return gravity;}
    void setGravity(int g) {gravity=g;}
    void setAlive(bool a) {alive=a;}
    bool isAlive() const {return alive;}
private:
    int health, maxHealth;
    struct cycle {
        int row;
        int w;
        int h;
        int amount;
        int speed;
        int tick;
    };
    vector<cycle> animations;
    int curAnim;
    int begin;
    bool rev, nAb;
    int newAnim;
    int speed;
    int gravity;
    bool alive;
};

#endif //ENTITY_H