#if __WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <stdio.h>
#include "maze.h"
#include "generate_maze.h"

void clear_screen(){
    #if __WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void sleep_screen(){
    #if __WIN32
        Sleep(800);
    #else
        sleep(1);
    #endif
}

Maze generate_maze(){
    int height = 0, width = 0;
    unsigned long long int seed = 0;

    while(1){
        cout << "Enter maze height: ";
        cin >> height;

        cout << "Enter maze width: ";
        cin >> width;

        if(height < 3 || width < 3 || height > 40 || width > 30)
            cout << "Invalid size(must be at least 3x3, at most 40x30)"
            << endl;
        else break;
    }
    cout << "Enter seed: ";
    cin >> seed;

    Maze maze(height, width, seed);

    if(dfs(maze.getHeight(), maze.getWidth(), maze.getGrid()) == NULL)
        maze.adjustMaze();

    return maze;
}

Maze read_from_file(const string& filename){
    ifstream file(filename);
    stringstream ss;
    string line;
    char element;
    int height = 0, width = 0;

    getline(file, line);
    ss << line;
    ss >> height >> width;
    Maze maze(height, width);

    for(int i = 0; i < height; i++){
        getline(file, line);
        for(int j = 0; j < width; j++){
            element = line[j];
            maze.writeToIndex(i, j, element);
        }
    }
    file.close();

    return maze;
}

void write_to_file(const Maze& maze, const string& filename){
    ofstream file(filename);
    if(!file){
        cout << "File doesn't exist!" << endl;
        return;
    }

    file << maze.getHeight() << " " << maze.getWidth() << endl;

    for(int i = 0; i < maze.getHeight(); i++){
        for(int j = 0; j < maze.getWidth(); j++)
            file << maze.getElement(i, j);
        file << endl;
    }
    file.close();
}

void crawl_by_user(Maze maze){
    int direction = 0, x = 0, y = 0, offset_x = 0, offset_y = 0;
    maze.writeToIndex(y, x, '.');

    while(1){
        maze.drawMaze();
        if(x == maze.getWidth() - 1 && y == maze.getHeight() - 1)
            return;

        cout << "Enter direction(1 - up, 2 - down, 3 - left, 4 - right, 5 - exit): " << endl;
        cin >> direction;

        offset_x = 0;
        offset_y = 0;

        clear_screen();

        switch(direction){
            case 1: offset_y = -1; break;
            case 2: offset_y = 1; break;
            case 3: offset_x = -1; break;
            case 4: offset_x = 1; break;
            case 5: return;
        }

        if(x + offset_x < 0 || x + offset_x == maze.getWidth() ||
           y + offset_y < 0 || y + offset_y == maze.getHeight())
            cout << "Can't go out of bounds!" << endl;
        else if(maze.getElement(y + offset_y, x + offset_x) == '#')
            cout << "You can't go into walls!" << endl;
        else{
            maze.writeToIndex(y, x, ' ');
            x += offset_x;
            y += offset_y;
            maze.writeToIndex(y, x, '.');
        }
    }

    cout << "You've reached the end of the maze!" << endl;
}

void crawl_by_computer(Maze maze){
    int choice = 0;
    list_t *path;

    cout << "Which algorithm do you want to use?" << endl;
    cout << "1.Right wall algorithm" << endl;
    cout << "2.A* algorithm" << endl;
    cin >> choice;

    if(choice == 1){
        path = dfs(maze.getHeight(), maze.getWidth(), maze.getGrid());
        path->head = path->head->next;
    }else
        path = astar(maze.getHeight(), maze.getWidth(), maze.getGrid());

    while(path->head){
        clear_screen();

        for(int i = 0; i < maze.getWidth(); i++)
            cout << "-";
        cout << endl;

        maze.writeToIndex(path->head->r, path->head->c, '.');
        maze.drawMaze();

        maze.writeToIndex(path->head->r, path->head->c, ' ');
        path->head = path->head->next;

        if(path->head)
            maze.writeToIndex(path->head->r, path->head->c, ' ');

        for(int i = 0; i < maze.getWidth(); i++)
            cout << "-";
        cout << endl << endl;

        sleep_screen();
    }
}

int main(){
    int choice = 0;
    Maze maze;

    while(1){
        cout << "1.Generate maze" << endl;
        cout << "2.Read from file" << endl;
        cout << "3.Write to file" << endl;
        cout << "4.Crawling by the user" << endl;
        cout << "5.Crawling by the computer" << endl;
        cout << "6.Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:{
                maze = generate_maze();
                clear_screen();
                break;
            }

            case 2:{
                maze = read_from_file("file.txt");
                clear_screen();
                break;
            }

            case 3:
                write_to_file(maze, "file.txt");
                clear_screen();
                break;

            case 4:
                crawl_by_user(maze);
                break;

            case 5:
                crawl_by_computer(maze);
                break;

            case 6:
                exit(0);

            default:
                cout << "Invalid option" << endl;
                break;
        }
    }
}
