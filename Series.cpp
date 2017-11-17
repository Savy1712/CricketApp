#include <cstring>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

class Series {
  public:
    std::string series;
    int number_of_teams_participating;
    int number_of_games;
    std::vector<std::string> teams;  
    std::string country;
    std::vector<std::string> venues;
 
    Series() : teams(0), venues(0) {
      this->series = "";
      this->country = "";
      this->number_of_teams_participating = 0;
      this->number_of_games = 0;
    }

    void get_country_to_venue(std::map<std::string, std::vector<std::string> > &CountryToVenue ) {
      CountryToVenue["Australia"]= {"Perth", "Brisbane", "Sydney"};
      CountryToVenue["India"] = {"Chennai", "Kolkatta", "Mumbai"};        
    }

    int add_venue_to_country(std::map<std::string, std::vector<std::string> > &CountryToVenue,
                             std::string country_name, std::vector<std::string> venues) {
      bool venue_found = false;
      for(int i = 0; i < venues.size(); i++) {
        for (int j = 0; j < CountryToVenue[country_name].size(); j++) {
          if(venues[i] == CountryToVenue[country_name][j]) {
            venue_found = true;
            break; 
          } 
        }
        if(!venue_found) {
          CountryToVenue[country_name].push_back(venues[i]);  
        }   
        venue_found = false;      
      }     
   
    }

    std::string get_series_name(std::string series_name) {
      this->series = series_name;
      return this->series;
    }
 
    std::string get_country_name(std::string country_name) {
      this->country = country_name;
      return this->country; 
    }

    int get_number_of_games(std::string games_count) {
      std::stringstream game_count(games_count);
      game_count >> this->number_of_games;
      return this->number_of_games; 
    }

    int get_number_of_teams_participating(std::string num_of_teams) {
      int teams_count;
      std::stringstream team_count(num_of_teams);
      team_count >> this->number_of_teams_participating;
      return this->number_of_teams_participating; 

    }
    void print(std::vector<std::string> val_arr, std::string name = "") {
      std::vector<std::string>::iterator it;
      for (it = val_arr.begin(); it != val_arr.end(); it++) {
        cout << name<< " " << *it << std::endl;
      }
    }

    void print_map(std::map<std::string, std::vector<std::string> > CountryToVenue) {
      std::map<std::string, std::vector<std::string> >::iterator it;
      for(it = CountryToVenue.begin(); it != CountryToVenue.end(); it++) {
        std::cout<< "\n Country :"<< it->first << std::endl;
        std::vector<std::string>::iterator vec_it;
        for(vec_it = it->second.begin(); vec_it != it->second.end(); vec_it++) {
          std::cout<< " Venues are : " << *vec_it << std::endl;
        }
      }
    }
};


int main() {
  
  Series series;

  /* Test Doc : for the sequence of operations */
  std::fstream test_doc; 
  test_doc.open("./TestDoc.txt", std::ios::in);
  std::stringstream file_open_string;
  file_open_string << test_doc.rdbuf();
  test_doc.close();
  std::string final_string = file_open_string.str();
 
  // Get the test buffer : sequence of operations
  std::string temp = "";
  std::vector<std::string> test_doc_buffer;
  for(int i = 0; i < final_string.length(); i++) {
    if (final_string[i] != '\n') {
      temp += final_string[i];
    } else {
        test_doc_buffer.push_back(temp);
        temp = "";
    }
  } 

  // Series name
  std::cout << "Series Name:" <<  series.get_series_name(test_doc_buffer[0]) << std::endl;
  // Number of teams participating
  std::cout << "Number of teams participating: " << series.get_number_of_teams_participating(test_doc_buffer[1]) << std::endl;
  // Get country name
  std::cout<< "Country: " << series.get_country_name(test_doc_buffer[2]) << std::endl;
  // Get Number of games in this series
  std::cout << "Number of games to be played in this series: "<< series.get_number_of_games(test_doc_buffer[3]) << std::endl; 
   
  /* Country to Venue mapping */ 
  std::map<std::string, std::vector<std::string> > CountryToVenue;
  series.get_country_to_venue(CountryToVenue);
  series.add_venue_to_country(CountryToVenue, "South Africa", {"Capetown","Durban"});
  series.print_map(CountryToVenue);

  return 0;
}

