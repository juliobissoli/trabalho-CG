#include "includes/read_svg.h"
#include <iostream>


void Read::loadinFile(string path){
    tinyxml2::XMLDocument svg;
    tinyxml2::XMLNode* main_element;
    tinyxml2::XMLElement* element;
    
    svg.LoadFile(path.c_str());
    main_element = svg.FirstChildElement("svg");

    element = main_element->FirstChildElement("rect");
    _readingRectangle(element);
    _readingCircle(element);

}


  void Read::_readingRectangle(tinyxml2::XMLElement* element){

        cout << " == read circle ==\n";
        double cx, cy, width, height;
        const char* fill;   
       while (element != NULL){
        element->QueryDoubleAttribute("x", &cx);
        element->QueryDoubleAttribute("y", &cy);
        element->QueryDoubleAttribute("width", &width);
        element->QueryDoubleAttribute("height", &height);
        element->QueryStringAttribute("fill",&fill);
        
        cout << "loading \t x " << cx << "\t y " << cy << "\t width " << width << "\t height " << height << "\t fill" << fill << endl;

        // if(!strcmp("blue",fill)){
        //     this -> centerX = cx;
        //     this -> centerY = cy;
        //     this -> width = width;
        //     this -> height = height;
        // } else if(!strcmp("black",fill)){
        //     cy = cy - this->centerY - this->height/2;
        //     cx = cx - this->centerX - this->width/2;
        //     Obstacle ob(cx + width/2,-cy -height,width,height);
        //     this->obstacles.push_back(ob);
        // } else{
        //     cout <<"Erro inesperado! " << endl;
        // }        
        element = element -> NextSiblingElement("rect");
    }

  }

   void Read::_readingCircle(tinyxml2::XMLElement* element){

        double x, y, r, width, height;
        const char* fill;   
       while (element != NULL){
        element->QueryDoubleAttribute("cx", &x);
        element->QueryDoubleAttribute("cy", &y);
        element->QueryDoubleAttribute("r", &r);
        element->QueryDoubleAttribute("width", &width);
        element->QueryDoubleAttribute("height", &height);
        element->QueryStringAttribute("fill",&fill);
        
        cout << "loading \t x " << x << "\t y " << y << "\t width " << width << "\t height " << height <<  "\t r " << r <<"\t fill " << fill << endl;

        // if(!strcmp("blue",fill)){
        //     this -> centerX = cx;
        //     this -> centerY = cy;
        //     this -> width = width;
        //     this -> height = height;
        // } else if(!strcmp("black",fill)){
        //     cy = cy - this->centerY - this->height/2;
        //     cx = cx - this->centerX - this->width/2;
        //     Obstacle ob(cx + width/2,-cy -height,width,height);
        //     this->obstacles.push_back(ob);
        // } else{
        //     cout <<"Erro inesperado! " << endl;
        // }        
        element = element -> NextSiblingElement("rect");
    }

  }
