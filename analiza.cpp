#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;


void Separator()
{
  cout << endl << "---------------------------------------------------------------" << endl;
}

int main()
{

  fstream file_1{ "passenger_type.csv" };
  if( !file_1 )
  {
  cout << "OPENING FIRST FILE ERROR!!!" << endl;
  return 0;
  }
  string s=""; //wiersz
  string word="";
  double all = 0; //string ze slowem
  double personal = 0;
  double business = 0;
  vector <string> line; //wektor z rekordem
  vector <string> pers;
  vector <string> busi;
  getline(file_1, s); //wczytanie nagłówków
  while( getline( file_1, s ) )
  {
    line.clear();
    stringstream ss(s);
    while( getline( ss, word, ';' ) )
    {
      line.push_back(word);
    }
    string travel_type = line[5];
    if( travel_type == "Personal Travel" )
    {
      personal += 1;
      all += 1;
      pers.push_back(travel_type);

    }
    else if( travel_type == "Business travel" )
    {
      business += 1;
      all += 1;
      busi.push_back(travel_type);
      
    }
    else 
    {
      all += 1;
    }
  }

  double personal_pc = (personal / all) * 100;
  double business_pc = (business / all) * 100;
  Separator();
  cout << "T Y P E   O F   T R A V E L   -   ANALIZE";
  Separator();
  cout << "Total number of flights: " << all << endl << endl;
  cout << "Number of Personal flights: " << personal <<  "\tIn percent: " << personal_pc << "%" << endl;
  cout << "Number of Business flights: " << business << "\tIn percent: " << business_pc << "%";
  Separator();
  cout << endl << endl;
  file_1.close();
  
  //-----------------------------------------------------------------
  //----- 2 File -----------------
  //-----------------------------------------------------------------

  
  fstream file_2{ "planecrashinfo.csv" };
  if (!file_2)
  {
    cout << "OPENING SECOND FILE ERROR!!!" << endl;
    return 0;
  }

  file_2.close();

  //-----------------------------------------------------------------
  //----- 3 File -----------------
  //-----------------------------------------------------------------

  fstream file_3{ "Invistico_Airline.csv" };
  if (!file_3)
  {
    cout << "OPENING FIRTH FILE ERROR!!!" << endl;
    return 0;
  }
  double all_3 = 0;
  double five = 0;
  double zero = 0;
  double other = 0;
  double cleanliness = 0;
  vector <double> clean;
  getline(file_3, s); //wczytanie nagłówków
  while (getline(file_3, s))
  {
    line.clear();
    stringstream ss(s); //moze byc to samo bo lokalna
    while (getline(ss, word, ','))
    {
      line.push_back(word);
    }
    string sRating = line[18];
    double dbRating = stod(sRating);
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
  double mean = cleanliness / all_3;
  Separator();
  cout << " C L E A N L I N E S S   R A T I N G    -    ANALIZE" ;
  Separator();
  cout << "Average rating for cleanliness on the plane:\t" << mean;
  Separator();
  cout << "Number of 0 stars:\t" << zero << endl;
  cout << "Number of 5 stars:\t" << five << endl;
  cout << "Number of ratings with a different number of stars:\t"<< other;
  Separator();
  if (mean < 4) { cout << "They have to improve their cleanliness level  :("; }
  else { cout << "They have a high level of cleanliness on board  :)"; }
  Separator();
  file_3.close();
  return 0;
}


