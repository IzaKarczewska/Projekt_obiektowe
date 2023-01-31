#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;
#define TEST

void Separator()
{
  cout << endl << "------------------------------------------------------------------" << endl;
}

int main()
{
  fstream file_1{ "passenger_type.csv" };
  if( !file_1 )
  {
  cout << "OPENING FIRST FILE ERROR!!!" << endl;
  return -1;
  }
  
  string s=""; //row
  string word="";
  double all = 0;
  double personal = 0;
  double business = 0;
  vector <string> line; //record
  vector <string> pers; 
  vector <string> busi;
  getline( file_1, s ); //header
  while( getline( file_1, s ) )
  {
    int col = 0;
    line.clear();
    stringstream ss( s );
    while( getline( ss, word, ';' ) )
    {
      line.push_back(word);
      col++;
      if( col == 6 )break; //to work faster
    }
    string travel_type = line[5]; // column with type of travel
    //.....................................
    if( travel_type == "Personal Travel" )
    {
      personal += 1;
      all += 1;
      pers.push_back( travel_type );

    }
    else if( travel_type == "Business travel" )
    {
      business += 1;
      all += 1;
      busi.push_back( travel_type );
      
    }
    else 
    {
      all += 1;
    }
  }
  //........................................
  double personal_pc = ( personal / all ) * 100;
  double business_pc = ( business / all ) * 100;
  Separator();
  cout << " T Y P E   O F   T R A V E L   -   ANALIZE";
  Separator();
  cout << " Total number of flights: " << all << endl << endl;
  cout << " Number of Personal flights: " << personal <<  "\tIn percent: " << personal_pc << "%" << endl;
  cout << " Number of Business flights: " << business << "\tIn percent: " << business_pc << "%" <<endl;
  Separator();
  cout << endl << endl;
  file_1.close();
 
  
  //-----------------------------------------------------------------
  //----- 2 File -----------------
  //-----------------------------------------------------------------

  Separator();
  cout << " P L A N E  C R A S H E S  -  fatalities each year   -   ANALIZE";
  Separator();

  fstream file_2{ "airplane_crash.csv" };
  if( !file_2 )
  {
    cout << " OPENING SECOND FILE ERROR!!!" << endl;
    return -1;
  }
  map <int, int> year; // map to group fatalities by year
  getline( file_2, s );
  
  while( getline( file_2, s ) )
  {
    line.clear();
    string word;
    stringstream ss( s );
    getline( ss, word, ',' ); //first field with date
    int l = word.length(); //we want to get only year from date
    int col = 0; //flag to ignore " , "
    word = word.substr( l - 4, 4 ); //choose the last 4 characters (year)
    if( word.length() != 4 ) //if we read the year wrong
    {
      cout << " ERROR in reading year from date! " << endl;
      return -2;
    }
    line.push_back( word );
    col++;
    while( getline( ss, word, ',' ) )
    {
      line.push_back( word );
      col++;
      
      if( col == 2 )
      {
        if( ss.get() == '"' )
        {
          getline( ss, word, '"' );
          ss.get(); //',' after '"'
          line.push_back( word );
          col++;
        }
        else
        {
          ss.unget();
          getline( ss, word, ',' );
          line.push_back( word );
          col++;
        }
      }
      if( col == 12 ) break; // don't read after the column we need
    }
    //................................
    string incidentYear = line[0];
    string numOfFatalities = line[10];
    int iIncidentYear;
    int iNumOfFatalities;
    try //wyjatek
    {
      iIncidentYear = stoi( incidentYear );
      iNumOfFatalities = stoi( numOfFatalities );
      if( year.find( iIncidentYear ) == year.end() )
      {
        year[ iIncidentYear ] = iNumOfFatalities; //creating new key
      }
      else
      {
        year[ iIncidentYear ] += iNumOfFatalities; //adding to recognized key
      }

    }
    catch (...)
    {

    }
    
  }
  int maximum = 0;
  int maxYear = 0;
  for( auto i : year ) //
  {
    if( i.second > maximum )
    {
      maxYear = i.first; //changing the year with most fatalities
      maximum = i.second; //changing the most number of fatalities
    }
  }
  //......................................
#ifdef TEST
  for( auto i : year ) //printing all of the yeras with number of fatalities
  {
    cout << "\tYear: " << i.first << " " << " Fatalities: " << i.second<< endl;
  }
#endif  
  //cout << year[maxYear];
  Separator();
  cout <<" The most fatalities: "<< maximum << "\tin year: " << maxYear;
  Separator();
  cout << endl << endl;
  file_2.close();

  //-----------------------------------------------------------------
  //----- 3 File -----------------
  //-----------------------------------------------------------------

  fstream file_3{ "Invistico_Airline.csv" };
  if( !file_3 )
  {
    cout << "OPENING FIRTH FILE ERROR!!!" << endl;
    return -1;
  }
  double all_3 = 0;
  double five = 0;
  double zero = 0;
  double other = 0;
  double cleanliness = 0;
  vector <double> clean;
  getline( file_3, s );
  while( getline( file_3, s ) )
  {
    int col = 0;
    line.clear();
    stringstream ss( s );
    while( getline( ss, word, ',' ) )
    {
      line.push_back( word );
      col++;
      if( col == 19 ) break;
    }
    string sRating = line[18];
    double dbRating = stod( sRating );
    cleanliness += dbRating;
    all_3 += 1;
    if( dbRating == 0 )
    {
      zero += 1;
    }
    else if( dbRating == 5 )
    {
      five += 1;
    }
    else
    {
      other += 1;
    }
  } 

  //...................................
  double mean = cleanliness / all_3;
  //..................................
  Separator();
  cout << " C L E A N L I N E S S   R A T I N G    -    ANALIZE" ;
  Separator();
  cout << " Number of 0 stars:\t" << zero << endl;
  cout << " Number of 5 stars:\t" << five << endl;
  cout << " Number of ratings with a different number of stars:\t"<< other;
  Separator();
  cout << " Average rating for cleanliness on the plane:\t" << mean;
  Separator();
  if( mean < 4 ) { cout << " They have to improve their cleanliness level  :("; }
  else { cout << " They have a high level of cleanliness on board  :)"; }
  Separator();
  file_3.close();
  return 0;
}


