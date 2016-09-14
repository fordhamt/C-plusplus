#include <iomanip>
#include <iostream>
#include "hashtable.h"
#include <string>
#include <cstring>
using namespace std;
using namespace cop4530;

void menu()
{
	cout << "\n\n";
	cout << "l - Load Dictionary From File" << endl;
	cout << "a - Add Word" << endl;
	cout << "r - Remove Word" << endl;
	cout << "c - Clear HashTable" << endl;
	cout << "f - Find Word" << endl;
	cout << "d - Dump HashTable" << endl;
	cout << "s - HashTable Size" << endl;
	cout << "w - Write to File" << endl;
	cout << "x - Exit program" << endl;
	cout << "\nEnter choice : ";
}

int main() {
  size_t size = 1301081;
  HashTable<string> h(size);
  string strtmp;
  char choice;
  const char * file = new char[ 100 ];
  do {
    menu();
    cin >> choice;

    switch( choice ) {
      case 'l' :
        cout << "Enter file name: ";
        cin >> strtmp;
        file = strtmp.c_str();
        //if( h.load( file ) )
           cout << "Dicitionary Loaded Successfully\n";
        break;
      case 'a' :

        break;
      case 'r' :

        break;
      case 'c' :

        break;
      case 'f' :

        break;
      case 'd' :

        break;
      case 's' :

        break;
      case 'w' :

        break;
      case 'x' :
        break;
      default :
	cout << "Invalid choice\n";
    }
    delete file;
  } while( choice != 'x' );
  return 0;
}
