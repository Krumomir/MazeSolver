#ifndef GENERATE_MAZE_H
#define GENERATE_MAZE_H
#include <iostream>

using namespace std;

class Maze{
    char** maze;
    int height, width;
    unsigned long long int seed;
public:
    Maze(){}

    Maze(int height, int width)
    :height(height), width(width){
        this->maze = new char*[height];

        for(int i = 0; i < height; i++)
            this->maze[i] = new char[width];
    }

    Maze(int height, int width, unsigned long long int seed)
    :height(height), width(width), seed(seed){
        maze = new char*[height];

        for(int i = 0; i < height; i++)
            maze[i] = new char[width];

        unsigned long long int temp = seed;
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                if(temp & 1) maze[i][j] = '#';
                else maze[i][j] = ' ';

                temp >>= 1;
                if((temp | 0) == 0) temp = seed * (j + 1) * (i + 1);
            }
        }

        maze[0][0] = ' ';
        maze[height - 1][width - 1] = ' ';
    }

    Maze& operator=(const Maze& other){
        if(this != &other){
            this->height = other.height;
            this->width = other.width;
            this->seed = other.seed;
            this->maze = new char*[height];

            for(int i = 0; i < height; i++)
                this->maze[i] = new char[width];

            for(int i = 0; i < height; i++)
                for(int j = 0; j < width; j++)
                    this->maze[i][j] = other.maze[i][j];
        }
        return *this;
    }

    const int getHeight()const{
        return height;
    }

    const int getWidth()const{
        return width;
    }

    const char getElement(int i, int j)const{
        return maze[i][j];
    }

    char** getGrid()const{
        return maze;
    }

    void writeToIndex(int i, int j, char c){
        maze[i][j] = c;
    }

    void adjustMaze(int currX = 0, int currY = 0, int lastDir = 6){
        if(currX == (width - 1) && currY == (height - 1)) return;

        switch(lastDir){
            case 0: lastDir = 2; break;
            case 1: lastDir = 3; break;
            case 2: lastDir = 0; break;
            case 3: lastDir = 1; break;
        }

        int offsetX = 0, offsetY = 0, direction = lastDir;
        while(direction == lastDir){
            direction = rand() % 6;
            if(direction >= 4) direction = 3;
            else if(direction >= 2) direction = 2;
        }

        switch(direction){
            case 0: offsetY = -1; break;
            case 1: offsetX = -1; break;
            case 2: offsetY = 1; break;
            case 3: offsetX = 1; break;
        }

        if(currX + offsetX < 0 || currX + offsetX >= width ||
           currY + offsetY < 0 || currY + offsetY >= height)
            adjustMaze(currX, currY, lastDir);
        else{
            currX += offsetX;
            currY += offsetY;
            maze[currY][currX] = ' ';
            adjustMaze(currX, currY, direction);
        }
    }

    void drawMaze(){
        for(int i = 0; i < this->height; i++){
            for(int j = 0; j < this->width; j++)
                cout << maze[i][j];

            cout << endl;
        }
    }

    ~Maze(){
        for(int i = 0; i < height; i++)
            delete [] maze[i];

        delete [] maze;
    }

};

#endif
