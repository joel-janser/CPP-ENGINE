//
//  Element.cpp
//  GameDemo
//
//  Created by Joel Janser on 03.02.19.
//  Copyright © 2019 CompiledCreations. All rights reserved.
//

#include "Element.hpp"
#include <iterator>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#define max(max, min) ((max) > (min) ? (max) : (min))



int Element::getX2() {
    return x + widthPixel;
}

int Element::getY2() {
    return y + heightPixel;
}

Element::Element(Element * superElement) {
    
        this->superElement = superElement;
  

}

Element * Element::findElement(int x, int y) {
    Element * currentElement = NULL;
    if ( x >= this->x && y >= this->y ) {
        if (this->getX2() > x && this->getY2() > y) {
            currentElement = this;
        }
    }
    for (Element * subelement: subelements) {
        Element * foundElement = subelement->findElement(x, y);
        if (foundElement != NULL) {
            currentElement = foundElement;
        }
    }
    
    return currentElement;
}

void Element::paint(SDL_Renderer* renderer) {
    SDL_Rect * r = new SDL_Rect();
    r->x = x;
    r->y = y;
    r->w = widthPixel;
    r->h = heightPixel;
   // SDL_SetRenderDrawColor(<#SDL_Renderer *renderer#>, <#Uint8 r#>, <#Uint8 g#>, <#Uint8 b#>, <#Uint8 a#>)
    
    SDL_SetRenderDrawColor( renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a );
    SDL_RenderFillRect(renderer, r);
    
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
    SDL_RenderDrawRect(renderer, r);
    
    for (Element * subelement: subelements) {
        subelement->paint(renderer);
    }
    
    
}

void Element::drawText(SDL_Renderer* renderer, char* string,
                       int size, int x, int y,
                       Uint8 fR, Uint8 fG, Uint8 fB, Uint8 fA) {
    
    TTF_Font* font = TTF_OpenFont("/Library/Fonts/Arial Unicode.ttf", size);
    if(!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }
    SDL_Color foregroundColor = { fR, fG, fB, fA };
//    SDL_Color backgroundColor = { bR, bG, bB, 0 };
    int w,h;
    if(TTF_SizeText(font,string,&w,&h)) {
        printf("....");
    }
    
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, string, foregroundColor);
    
    SDL_Rect textLocation = { x, y, w, h };
    SDL_Rect src = {0,0,w,h};
    
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    SDL_RenderCopy(renderer, Message, &src, &textLocation);
    
    TTF_CloseFont(font);
    
}


void Element::render(int x, int y) {
    int currentX = x;
    int currentY = y;
    int maxUsedHeight = 0;
    int maxY = 0;
    int maxX = 0;
    
    int lineY = y;
    
    if (widthType == pixel) {
        widthPixel = width;
    }
    
    if (heightType == pixel) {
        heightPixel = height;
    }
    if (heightType == content_sized) {
        heightPixel = superElement->heightPixel;
    }
    
    if (widthType == content_sized) {
        widthPixel = superElement->widthPixel - superElement->spaceLeft - superElement->spaceRight;
    }
    
    if (widthType == percent) {
        if (superElement->widthPixel != -1) {
            int maxWidth = superElement->widthPixel - superElement->spaceLeft - superElement->spaceRight;
            widthPixel = maxWidth * width / 100;
            //System.out.println("Super: " + this.superElement.widthPixel + " " + widthPixel);
        } else {
            // Implement
           // System.err.println("Ein Fehler ist aufgetreten");
        }
    }
    
    if (heightType == percent) {
        if (superElement->heightPixel != -1) {
            heightPixel = superElement->heightPixel / 100 * height;
        } else {
            // Implement
        }
    }
    
    int maxContentWidth = widthPixel;
    //if (superElement != NULL) {
        maxContentWidth = widthPixel - spaceLeft - spaceRight;
    //}
    
    int usedHeight = 0;
    int lineHeight = 0;
    
    Element * lastElement = NULL;
    
 
    
    for (Element * subelement: subelements) {
        //Element * subelement = *_itSubElement;
    
        if (subelement->flowType == vertical) {
            currentX = x; // align-type (?)
        }
        if (subelement->flowType == horizontal) {
            currentY = lineY;
        }
        
        if (currentX == x) {
            subelement->x = x + max(spaceLeft, subelement->distanceLeft);
        } else {
            subelement->x = lastElement->getX2() + max(lastElement->distanceRight, distanceLeft);
        }
        if (currentY == y) {
            subelement->y = y + max(spaceTop, subelement->distanceTop);
        } else {
            subelement->y = lastElement->getY2() + max(lastElement->distanceBottom, distanceTop);
        }
        //
        subelement->render(subelement->x, subelement->y);
        
        if (flowType == horizontal) {
            //    if (widthType == SizeType.PIXEL || widthType == widthType.PERCENT) {
            if ( (currentX > x) && (subelement->getX2() > (getX2() - spaceRight))) {
                subelement->x = x + max(spaceLeft, subelement->distanceLeft);
                currentY += lineHeight;
                subelement->y = maxY;
                lineHeight = 0;
            } else {
                lineHeight = max(lineHeight, subelement->height);
            }
            currentX = subelement->x + subelement->widthPixel;
            //} else {
            //    lineHeight = Math.max(lineHeight, subelement->height);
            // subelement->x = x + Math.max(spaceLeft, subelement->distanceLeft);
            //}
            // lineWidth+= subelement->widthPixel;
            // maxUsedWidth =Math.max(lineWidth, maxUsedWidth);
            // }
        } else if (flowType == vertical) {
            int leftSpace = max(subelement->distanceLeft, spaceLeft);
            int rightSpace = max(subelement->distanceRight, spaceRight);
            // lineWidth = 0;
            usedHeight += subelement->height;
            currentY += subelement->height;
            
            lineY += subelement->height;
            maxUsedHeight = max(usedHeight, maxUsedHeight);
        }
        int newMaxY = subelement->y + subelement->heightPixel + max(subelement->distanceBottom, spaceBottom);
        if (maxY < newMaxY) {
            maxY = newMaxY;
        }
        int newMaxX = subelement->x + subelement->widthPixel + max(subelement->distanceRight, spaceRight);
        if (maxX < newMaxX) {
            maxX = newMaxX;
        }
        
        lastElement= subelement;
    }
    
    if (widthType == content_sized) {
        widthPixel = maxX - x;
    }
    if (heightType == content_sized) {
        heightPixel = maxY - y;
    }
}


void Element::setDistance(int distance) {
    distanceTop = distance;
    distanceLeft = distance;
    distanceRight = distance;
    distanceBottom = distance;
}

void Element::setSpace(int space) {
    spaceTop = space;
    spaceLeft = space;
    spaceRight = space;
    spaceBottom = space;
}
