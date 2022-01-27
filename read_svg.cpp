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

        if(!strcmp("blue", fill)){
             gX =      cx;
             gY =      cy;
             gWidth =  width;
             gHeight = height;
        }
         else if(!strcmp("black",fill)){
          // cy = cy - gY - gHeight/2;
          // cx = cx - gX - gWidth/2;
          tuple<double,double,double,double> rec = make_tuple(cx - gX  , cy - gY, width, height);
            _rec_list.push_back(rec);
            // cy = cy - this->centerY - this->height/2;
            // cx = cx - this->centerX - this->width/2;
            // Obstacle ob(cx + width/2,-cy -height,width,height);
            // this->obstacles.push_back(ob);
        } 
        //else{
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
        element = element -> NextSiblingElement("circle");

      if(!strcmp("green", fill)){
        cout << "Acho playa \n";
        cout << "x= " << x <<  "\ty= " << y << "\tgx= " << gX << "\tgy= " << gY << endl; 
        cout << "width= " << width <<  "\theight= " << height << endl; 
        cout << "x- gX - width/2= " << x- gX - width/2 <<  "\ty - gY - height= " << y - gY - height << endl; 
        
        
        _player_rec = make_tuple(x- gX, y - gY, r);

      }
      else if(!strcmp("red",fill)){
        tuple<double,double,double> circ = make_tuple(x- gX , y - gY, r);
        _circ_list.push_back(circ);
      }
    }

  }

  void Read::printTeste(){
    
    cout << "====== obstaculos ========== \n";
    for(auto r : _rec_list){
      cout << "[" << get<0>(r) << ", " << get<1>(r) << "]\t width = " <<  get<2>(r) << "\t height = " << get<3>(r) << endl;
    }

    cout << "\n ====== oponentes ========== \n";
    for(auto c : _circ_list){
      cout << "[" << get<0>(c) << ", " << get<1>(c) << "\t r = " <<  get<2>(c) << endl;
    }

  }


