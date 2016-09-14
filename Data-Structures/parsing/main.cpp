#include "as.h"

bool neighborSize(AS  as1, AS  as2) {
	if (as1.getNumNeighbors() != as2.getNumNeighbors())
		return as1.getNumNeighbors() > as2.getNumNeighbors();

	return as1.getASint() < as2.getASint();
}

int main( ) {

  char charRead;
  string stringTemp;

  vector<char> charArray;

  vector<string> dupList;
  vector<string> masterList;
  vector<AS> asList;

  AS *a1 = NULL;

  int position = 0;
  int count = 0;
  int barCounter = 0;
  int size = 0;
  string bar = "|";
  int flagcount= 0;
  bool duplicate = false;
  bool assetFlag = false;

  while (!cin.eof()) {
	  if (cin.eof())
		  break;

	  ////////   FOUND 14 of "|" = END OF FIRST LINE
	  //////////  START OF DATA PROCESSING
    if( barCounter >= 14 ) {

      assetFlag = false;
      duplicate = false;
	  position = 0;
      barCounter = 0;
	  masterList.clear( );
      
	  ////// CONVERT CHAR ARRAY OF READ IN DATA TO STRINGS
	  string char2string( charArray.begin( ), charArray.end( ));
      istringstream iss( char2string );
      copy( istream_iterator<string>( iss ), istream_iterator<string>( ), back_inserter( masterList ));
	 

      size = masterList.size( );

	  // ADD EACH NUMBER STRING IN MASTERLIST TO ASLIST
      for( int i = 0; i < size; i++) {

		duplicate = false;
        a1 = new AS;
    
		////// CHECK IF AT LAST STRING
	    if( i == size - 1 ) {
			for (int j = 0; j < asList.size(); j++) {
				if (masterList[size - 1] == asList[j].getAS()) {
				position = j;
				duplicate = true;
				break;
			    }
			}

			//// IF NEW AS
			if (!duplicate) {
				a1->writeAS(masterList[size - 1]);

				//// IF ARRAY HAS MORE THAN ONE ELEMENT
				if (size - 2 >= 0) {
					if (masterList[size - 2] != masterList[size - 1])
					  a1->writeNeighbor(masterList[size - 2]);
				}
			}
			else{
				///// IF AS EXISTS 
				if (((size - 2) >= 0 )) {
					if (!asList[position].isDuplicate(masterList[size - 2]) && masterList[size - 2] != asList[position].getAS())
						asList[position].writeNeighbor(masterList[size - 2]);
				}
			}
        }
        else {
			///// FOR ALL OTHER STRINGS
			for (int k = 0; k < asList.size(); k++) {
					if (masterList[i] == asList[k].getAS()) {
						position = k;
						duplicate = true;
						break;
					}
			}
			
			////// IF NEW AS
			if (!duplicate)
              a1->writeAS( masterList[ i ] );

			///// IF LIST IS BIGGER THAN 1
			if (i == 0 && ((i + 1) < size)) {
				if (duplicate) {
					if (!asList[position].isDuplicate(masterList[i + 1]) && masterList[i + 1] != asList[position].getAS())
						asList[position].writeNeighbor(masterList[i + 1]);
				}
				else {
					if (masterList[i + 1] != masterList[i])
					  a1->writeNeighbor(masterList[i + 1]);
				}
            }
			else{
				//// WRITE THE NEIGHBORS TO LEFT AND RIGHT OF CURRENT AS
				if (!duplicate) {
					///// CHECK IF AS HAS NEIGHBOR TO RIGHT
					if ((i + 1) < size) {
						if (masterList[i + 1] != masterList[i])
						  a1->writeNeighbor(masterList[i + 1]);
					}

					///// CHECK IF AS HAS NEIGHBOR TO LEFT
					if ((i - 1) >= 0) {
						if (masterList[i - 1] != masterList[i])
							a1->writeNeighbor(masterList[i - 1]);
					}
				}
				else {
					///// CHECK IF AS HAS NEIGHBOR TO RIGHT
					if ((i + 1) < size){
						if (!asList[position].isDuplicate(masterList[i + 1])) {
							if (masterList[i + 1] != asList[position].getAS())
								asList[position].writeNeighbor(masterList[i + 1]);
						}
					}
					///// CHECK IF AS HAS NEIGHBOR TO LEFT
					if ((i - 1) >= 0) {
						if (!asList[position].isDuplicate(masterList[i - 1])) {
							if (masterList[i - 1] != asList[position].getAS())
								asList[position].writeNeighbor(masterList[i - 1]);
						}
					}
				}
          }
        } 

		if (!duplicate)
			asList.push_back( *a1 );
		
      }

	  charArray.clear();
    }

	//// AS DATA FOUND READ CHARS INTO VECTOR
    if( (barCounter <= 6 && barCounter > 5) && !assetFlag ) {
      charRead = cin.get( );
        
	  if (cin.eof())
		  break;

	  if (charRead != '|' && charRead != '[')
        charArray.push_back( charRead );
    }
    else
      charRead = cin.get( );
      
	if (cin.eof())
		break;

	if (charRead == '[')
		assetFlag = true;

	////// COUNT THE | TO FIND AS DATA
	if (charRead == '|') {
		barCounter++;
		flagcount++;
	}
     

    count++;
 
  }
  cout << endl;

  
  sort(asList.begin(), asList.end(), neighborSize);
  for( vector<AS>::iterator itr = asList.begin( ); itr != asList.end( ); itr++)
    itr->print( );

  delete a1;  

  return 0;
}
