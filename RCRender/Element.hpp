//
//  Element.hpp
//  GameDemo
//
//  Created by Joel Janser on 03.02.19.
//  Copyright © 2019 CompiledCreations. All rights reserved.
//

#ifndef Element_hpp
#define Element_hpp

#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>
#include <string>


using namespace std;

enum SizeType { pixel = 0, percent = 1, content_sized = 2, remaining_percent = 3 };
enum FlowType { vertical = 0, horizontal = 1 };

class Element {
public:
    Element * findElement(int x, int y);
    void paint(SDL_Renderer* renderer);
    std::vector<Element*> subelements;
    int x = 0, y = 0, width = 0, height = 0, widthPixel = 0, heightPixel = 0, distanceTop = 0, distanceBottom = 0, distanceLeft = 0, distanceRight = 0, spaceTop = 0, spaceLeft = 0, spaceRight = 0, spaceBottom = 0;
    SizeType widthType = content_sized, heightType = content_sized;
    FlowType flowType = vertical;
    string name;
    Element * superElement = NULL;
    
    Element(Element * superElement);
    SDL_Color backgroundColor;
    SDL_Color borderColor;
    void set_values (int,int);
    void render(int x, int y);
    void setSpace(int x);
    void setDistance(int distance);
    void drawText(SDL_Renderer* renderer, char* string, int size, int x, int y, Uint8 fR, Uint8 fG, Uint8 fB, Uint8 fA);
private:
    int getX2();
    int getY2();
};

#endif /* Element_hpp */
