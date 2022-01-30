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

    // int ajuste = 1;
    // if(y < centerY) ajuste = -1; 
    // double dif_center = (y - centerY);

    // double y = dy - gY - centerY;
    double y = dy - gY - centerY;
    // cout << "center " << centerY << endl;
    // cout << "dy " << dy << "\t gY" << gY << "\t height " << height << "\t y = " << y << "\t y - height = " << y - height  << endl;
    // return y - (dif_center * ajuste);
    return -y - height;
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
        

        if(!strcmp("blue", fill)){
             gX =      cx;
             gY =      cy;
             gWidth =  width;
             gHeight = height;
        }
        // && width >= 10.0 && width < 11.0
         else if(!strcmp("black",fill)){
          tuple<double,double,double,double> rec = make_tuple((cx - gX) +(width/2)   , _ajusteY(cy, height), width, height);
            _rec_list.push_back(rec);
        } 
        //else{
        //     cout <<"Erro inesperado! " << endl;
        // }        
        element = element -> NextSiblingElement("rect");
    }

    //  ======== Remover depois dos testes
    tuple<double,double,double,double> rec1 = make_tuple(0, 0, 10, 10);
    tuple<double,double,double,double> rec2 = make_tuple(0, gHeight, 10, 10);
    tuple<double,double,double,double> rec3 = make_tuple(gWidth/2, gHeight/2, 30, 3);
    tuple<double,double,double,double> rec4 = make_tuple(gWidth, gHeight, 10, 10);
    tuple<double,double,double,double> rec5 = make_tuple(gWidth, 0, 10, 10);

    _rec_fake_list.push_back(rec1);    
    _rec_fake_list.push_back(rec2);    
    _rec_fake_list.push_back(rec3);    
    _rec_fake_list.push_back(rec4);  
    _rec_fake_list.push_back(rec5);  
      
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
        
        // cout << "loading \t x " << x << "\t y " << y << "\t width " << width << "\t height " << height <<  "\t r " << r <<"\t fill " << fill << endl;       
        element = element -> NextSiblingElement("circle");

      cout << "Ciculos \n";
      if(!strcmp("green", fill)){
        
        _player_rec = make_tuple(x- gX, y - gY, r);

      }
      else if(!strcmp("red",fill)){

        tuple<double,double,double> circ = make_tuple(x- gX, _ajusteY(y, 0), r);
        cout << "circulo x "<< x - gX << " y = " << _ajusteY(y, r) << endl;
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


