
#ifndef DB_ELEMENTS_HPP
#define DB_ELEMENTS_HPP

// forward declarations
//class Element;
class DB_Nodes;
class DB_Parts;
class FEMFile;

// includes
#include <vector>
#include <map>
#include "Element.hpp"

using namespace std;

class DB_Elements {

private:
  FEMFile* femfile;
  DB_Nodes* db_nodes;
  DB_Parts* db_parts;
  map<int,Element*> elements2;
  map<int,Element*> elements4;
  map<int,Element*> elements8;
  map<int,Element*> elements2ByIndex;
  map<int,Element*> elements4ByIndex;
  map<int,Element*> elements8ByIndex;

public:
  DB_Elements(FEMFile* _femfile);
  ~DB_Elements();
  FEMFile* get_femfile();
  DB_Nodes* get_db_nodes();
  Element* add_element(ElementType,int,vector<int>);

  unsigned int size();
  Element* get_elementByID(int,int);
  Element* get_elementByIndex(int,int);

};

#endif