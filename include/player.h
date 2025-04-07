#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL.h>
#include <vector>
using namespace std;

class Player {
    public:
    static const int rad = 16;
    // Constructor
    Player();
    
    // Methods
    void move(vector<vector<int>> tilemap_collision);
    void setPos(int x, int y);
    vector<int> getPos();
    void setVelX(int x);
    void setVelY(int y);
    
    private:
    int posX;
    int posY;
    int velX;
    int velY;
    bool checkCollision(int xs, int ys);

};

#endif /* _PLAYER_H_ */