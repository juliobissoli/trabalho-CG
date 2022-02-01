#include "../includes/read_svg.h"
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

  double Read::_ajusteY(double dy, double height){
    double centerY = gHeight;
    double y = dy - gY - centerY;
    return -y - height;
  }


  void Read::_readingRectangle(tinyxml2::XMLElement* element){

        double cx, cy, width, height;
        const char* fill;

       while (element != NULL){
        element->QueryDoubleAttribute("x", &cx);
        element->QueryDoubleAttribute("y", &cy);
        element->QueryDoubleAttribute("width", &width);
        element->QueryDoubleAttribute("height", &height);
        element->QueryStringAttribute("fill",&fill);
        

        if(!strcmp("blue", fill)){
             gX =      cx;
             gY =      cy;
             gWidth =  width;
             gHeight = height;
        }
         else if(!strcmp("black",fill)){
          tuple<double,double,double,double> rec = make_tuple((cx - gX) +(width/2)   , _ajusteY(cy, height), width, height);
            _rec_list.push_back(rec);
        }   
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
        
        element = element -> NextSiblingElement("circle");

      if(!strcmp("green", fill)){
        
        _player_rec = make_tuple(x- gX,  _ajusteY(y, 0), r);

      }
      else if(!strcmp("red",fill)){

        tuple<double,double,double> circ = make_tuple(x- gX, _ajusteY(y, 0), r);
        _circ_list.push_back(circ);
      }
    }

  }

  void Read::printTeste(){
    
    cout << "====== obstacles ========== \n";
    for(auto r : _rec_list){
      cout << "[" << get<0>(r) << ", " << get<1>(r) << "]\t width = " <<  get<2>(r) << "\t height = " << get<3>(r) << endl;
    }

    cout << "\n ====== oponentes ========== \n";
    for(auto c : _circ_list){
      cout << "[" << get<0>(c) << ", " << get<1>(c) << "\t r = " <<  get<2>(c) << endl;
    }

  }


