/* Your code here! */
#include "maze.h"
#include <stdlib.h>
#include <queue>

using namespace std;
using namespace cs225;

SquareMaze::SquareMaze(){
    width=0;
    height =0;
}

    /**
     * Makes a new SquareMaze of the given height and width.
     *
     * If this object already represents a maze it will clear all the
     * existing data before doing so. You will start with a square grid (like
     * graph paper) with the specified height and width. You will select
     * random walls to delete without creating a cycle, until there are no
     * more walls that could be deleted without creating a cycle. Do not
     * delete walls on the perimeter of the grid.
     *
     * Hints: You only need to store 2 bits per square: the "down" and
     * "right" walls. The finished maze is always a tree of corridors.)
     *
     * @param width The width of the SquareMaze (number of cells)
     * @param height The height of the SquareMaze (number of cells)
     */
    void SquareMaze::makeMaze(int width, int height){
        this->width = width;
        this->height = height;
        wall.resize(width);
        for(int i=0;i<width;i++){
            wall[i].resize(height);
            for(int j=0;j<height;j++){
                wall[i][j].resize(2);
                wall[i][j][0] = true;
                wall[i][j][1] = true;
            }
        }        
        connect.addelements(width*height);
        while(connect.size(0)!= width*height){
            int w = rand()%width;
            int h = rand()%height;
            int dir = rand()%2;
            if(w!=width-1 && dir==0){
                if(wall[w][h][0]==true && (connect.find(h*width+w) != connect.find(h*width+w+1))){
                    connect.setunion(h*width+w, h*width+w+1);
                    setWall(w,h,0,false);
                }
            }
            else if(h!=height-1 && dir == 1){
                if(wall[w][h][1]==true && (connect.find(h*width+w) != connect.find((h+1)*width+w))){
                    connect.setunion(h*width+w, (h+1)*width+w);
                    setWall(w,h,1,false);
                }
            }
        }
    }

    /**
     * This uses your representation of the maze to determine whether it is
     * possible to travel in the given direction from the square at
     * coordinates (x,y).
     *
     * For example, after makeMaze(2,2), the possible input coordinates will
     * be (0,0), (0,1), (1,0), and (1,1).
     *
     * - dir = 0 represents a rightward step (+1 to the x coordinate)
     * - dir = 1 represents a downward step (+1 to the y coordinate)
     * - dir = 2 represents a leftward step (-1 to the x coordinate)
     * - dir = 3 represents an upward step (-1 to the y coordinate)
     *
     * You can not step off of the maze or through a wall.
     *
     * This function will be very helpful in solving the maze. It will also
     * be used by the grading program to verify that your maze is a tree that
     * occupies the whole grid, and to verify your maze solution. So make
     * sure that this function works!
     *
     * @param x The x coordinate of the current cell
     * @param y The y coordinate of the current cell
     * @param dir The desired direction to move from the current cell
     * @return whether you can travel in the specified direction
     */
    bool SquareMaze::canTravel(int x, int y, int dir) const{
        switch(dir){
            case 0:
                if(0<=x && x < width-1 && wall[x][y][0]==false)return true;
                break;
            case 1:
                if(0<=y && y < height-1 && wall[x][y][1]==false)return true;
                break;
            case 2:
                if(width-1>=x && x >0 && wall[x-1][y][0]==false)return true;
                break;
            case 3:
                if(height-1>=y && y>0 && wall[x][y-1][1]==false)return true;
                break;
        }
        return false;
    }

    /**
     * Sets whether or not the specified wall exists.
     *
     * This function should be fast (constant time). You can assume that in
     * grading we will not make your maze a non-tree and then call one of the
     * other member functions. setWall should not prevent cycles from
     * occurring, but should simply set a wall to be present or not present.
     * Our tests will call setWall to copy a specific maze into your
     * implementation.
     *
     * @param x The x coordinate of the current cell
     * @param y The y coordinate of the current cell
     * @param dir Either 0 (right) or 1 (down), which specifies which wall to
     * set (same as the encoding explained in canTravel). You only need to
     * support setting the bottom and right walls of every square in the grid.
     * @param exists true if setting the wall to exist, false otherwise
     */
    void SquareMaze::setWall(int x, int y, int dir, bool exists){
        wall[x][y][dir] = exists;
    }

    /**
     * Solves this SquareMaze.
     *
     * For each square on the bottom row (maximum y coordinate), there is a
     * distance from the origin (i.e. the top-left cell), which is defined as
     * the length (measured as a number of steps) of the only path through
     * the maze from the origin to that square.
     *
     * Select the square in the bottom row with the largest distance from the
     * origin as the destination of the maze. solveMaze() returns the
     * winning path from the origin to the destination as a vector of
     * integers, where each integer represents the direction of a step, using
     * the same encoding as in canTravel().
     *
     * If multiple paths of maximum length exist, use the one with the
     * destination cell that has the smallest x value.
     *
     * Hint: this function should run in time linear in the number of cells
     * in the maze.
     *
     * @return a vector of directions taken to solve the maze
     */
    std::vector<int> SquareMaze::solveMaze(){
        std::vector<std::vector<bool>> visit;
        visit.resize(width);
        for(int i=0;i<width;i++){
            visit[i].resize(height);
            for(int j=0;j<height;j++){
                visit[i][j] = false;
            }
        }
        visit[0][0] = true;
        std::queue<int> bfs;
        bfs.push(0);
        std::vector<std::vector<int>> length;
        length.resize(width);
        for(int i=0;i<width;i++){
            length[i].resize(height);
            for(int j=0;j<height;j++){
                length[i][j] = -1;
            }
        }
        std::vector<int> prev_step;
        prev_step.resize(width*height, -1);
        while(bfs.empty()==false){
            int curr = bfs.front();
            bfs.pop();
            int w = curr%width;
            int h = curr/width;
            if(canTravel(w,h,0) && visit[w+1][h]==false){
                prev_step[curr+1] = curr;
                length[w+1][h] = length[w][h] + 1;
                visit[w+1][h] = true;
                bfs.push(curr+1);
            }
            if(canTravel(w,h,2) && visit[w-1][h]==false){
                prev_step[curr-1] = curr;
                length[w-1][h] = length[w][h] + 1;
                visit[w-1][h] = true;
                bfs.push(curr-1);
            }
            if(canTravel(w,h,1) && visit[w][h+1]==false){
                prev_step[curr+width] = curr;
                length[w][h+1] = length[w][h] + 1;
                visit[w][h+1] = true;
                bfs.push(curr+width);
            }
            if(canTravel(w,h,3) && visit[w][h-1]==false){
                prev_step[curr-width] = curr;
                length[w][h-1] = length[w][h] + 1;
                visit[w][h-1] = true;
                bfs.push(curr-width);
            }
        }

        int longest = 0;
        int longest_pos = 0;
        for(int i=0;i<width;i++){
            if(length[i][height-1]>longest){
                longest = length[i][height-1];
                longest_pos = width*(height-1)+i;
            }
        }
        std::vector<int> path;
        while(longest_pos!=0){
            int diff = longest_pos-prev_step[longest_pos];
            if(diff==1){
                path.insert(path.begin(),0);
            }
            else if(diff==width){
                path.insert(path.begin(),1);
            }
            else if(diff==-1){
                path.insert(path.begin(),2);
            }
            else{
                path.insert(path.begin(),3);
            }
            longest_pos = prev_step[longest_pos];
        }
        return path;
    }

    /**
     * Draws the maze without the solution.
     *
     * First, create a new PNG. Set the dimensions of the PNG to
     * (width*10+1,height*10+1). where height and width were the arguments to
     * makeMaze. Blacken the entire topmost row and leftmost column of
     * pixels, except the entrance (1,0) through (9,0).  For each square in
     * the maze, call its maze coordinates (x,y). If the right wall exists,
     * then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from
     * 0 to 10. If the bottom wall exists, then blacken the pixels with
     * coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
     *
     * The resulting PNG will look like the sample image, except there will
     * be no exit from the maze and the red line will be missing.
     *
     * @return a PNG of the unsolved SquareMaze
     */
    PNG* SquareMaze::drawMaze() const{
        PNG* maze = new PNG(width*10+1, height*10+1);
        maze->getPixel(0,0) = HSLAPixel(0,0,0);
        for(int i=10;i<width*10+1;i++){
            maze->getPixel(i,0) = HSLAPixel(0,0,0);
        }
        for(int i=0;i<height*10+1;i++){
            maze->getPixel(0,i) = HSLAPixel(0,0,0);
        }
        for(int w=0;w<width;w++){
            for(int h=0;h<height;h++){
                if(wall[w][h][0]){
                    for(int k=0;k<=10;k++){
                        maze->getPixel((w+1)*10,h*10+k) = HSLAPixel(0,0,0);
                    }
                }
                if(wall[w][h][1]){
                    for(int k=0;k<=10;k++){
                        maze->getPixel(w*10+k,(h+1)*10) = HSLAPixel(0,0,0);
                    }
                }
            }
        }
        return maze;
    }

    /**
     * This function calls drawMaze, then solveMaze; it modifies the PNG
     * from drawMaze to show the solution vector and the exit.
     *
     * Start at pixel (5,5). Each direction in the solution vector
     * corresponds to a trail of 11 red pixels in the given direction. If the
     * first step is downward, color pixels (5,5) through (5,15) red. (Red is
     * 0,1,0.5,1 in HSLA). Then if the second step is right, color pixels (5,15)
     * through (15,15) red. Then if the third step is up, color pixels
     * (15,15) through (15,5) red. Continue in this manner until you get to
     * the end of the solution vector, so that your output looks analogous
     * the above picture.
     *
     * Make the exit by undoing the bottom wall of the destination square:
     * call the destination maze coordinates (x,y), and whiten the pixels
     * with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
     *
     * @return a PNG of the solved SquareMaze
     */
    cs225::PNG* SquareMaze::drawMazeWithSolution(){
        PNG * solution = drawMaze();
        vector<int> path = solveMaze();
        int w = 5;
        int h = 5;
        for(int i=0;i<(int)path.size();i++){
            HSLAPixel red = HSLAPixel(0,1,0.5,1);
            switch(path[i]){
                case(0):
                    for(int j=0;j<=10;j++){
                        solution->getPixel(w+j,h) = red;
                    }
                    w+=10;
                    break;
                    
                case(1):
                    for(int j=0;j<=10;j++){
                        solution->getPixel(w,h+j) = red;
                    }
                    h+=10;
                    break;
                case(2):
                    for(int j=0;j<=10;j++){
                        solution->getPixel(w-j,h) = red;
                    }
                    w-=10;
                    break;
                case(3):
                    for(int j=0;j<=10;j++){
                        solution->getPixel(w,h-j) = red;
                    }
                    h-=10;
                    break;
            }
        }
        h+=5;
        for(int i=-4;i<5;i++){
            solution->getPixel(w+i,h).l = 1;
            solution->getPixel(w+i,h).a = 1;
        }
        return solution;
    }