using namespace std;
#include <vector>
#include <fstream>
#include <iostream>
#include <string>


struct city;

struct road
{
	string name;
	int length;
	city * A, * B;
};

struct city
{
	int code;   
	string state;  
	string name;   
	int population;  
	double area;  
	double latitude;   
	double longitude;   
	int intersection;   
	double distance;    
	int times;    
	city * next_hash;
};

const int arrsize = 700000;
city * arr[arrsize];

city * search(string word, city * list)
{    
	bool is_state = false;   
	if (word.size() == 2 && (int)(word[1]) <= 90)   
		is_state = true;  
	while (list != NULL)
	{        
		string compare = list->name;    
		if (is_state == true) 
			compare = list->state;    
		if (compare == word)       
			return list;        
		list = list->next_hash;    
	}    
	return NULL;
}

string delete_space(const string & s)
{ 
	int last;    
	last = s.size() - 1;  
	while (last >= 0 && s[last] == ' ')
	{        
		--last;
	}    
	return s.substr(0, last + 1);
}

int length(city * list)
{ 
	int len = 0;  
	while (list != NULL)   
	{ 
		len += 1;    
		list = list->next_hash; 
	}  
	return len; 
}

int hvalue(string s)
{ 
	int value = 76679;    
	for (int i = 0; i < s.length(); i += 1)    
		value = value * 691 + s[i];   
	if (value < 0)        
		value = - value;  
	return value % arrsize; 
}

void print(city * list)
{   
	if(list!=NULL)
	{        
		cout << list->code << "" << list->state << " " << list->name << " " << list->population << " " << list->area << " " << list->latitude << " " << list->longitude << " " << list->intersection << " " << list-> distance << "\n";   
		print(list = list->next_hash);    
	}
}

int main()
{       
	for (int i = 0; i < arrsize; i += 1)       
		arr[i] = NULL;    
	ifstream inf;
	inf.open("/home/www/class/een318/named-places.txt");
	if(inf.fail())
	{
		cout << "Failed to read data file!";
	}
	else
	{
		string s;   
		while (getline(inf, s))    
		{        
		  int code = std::stoi(s.substr(0, 8));       
		  string state = s.substr(8, 2);    
		  string name = delete_space(s.substr(10, 49));      
		  int population = std::stoi(s.substr(59,11));    
		  double area = std::stod(s.substr(70, 11)); 
		  double latitude = std::stod(s.substr(81, 10));     
		  double longitude = std::stod(s.substr(91, 11));
		  int intersection = std::stoi(s.substr(102, 5));  
		  double distance = std::stod(s.substr(107, 7));
		  int pos = hvalue(name);      
		  city * obj = search(name, arr[pos]);              
		  obj = new city;        
		  obj->next_hash = arr[pos];        
		  arr[pos] = obj;   
		  obj->code = code;   
		  obj->name = name;    
		  obj->state = state;     
		  obj->population = population;       
		  obj->area = area;       
		  obj->latitude = latitude;        
		  obj->longitude = longitude;       
		  obj->intersection = intersection;        
		  obj-> distance = distance;
		}    
	inf.close();  
	cout << "Hello, here are commands you can enter that the program will perform:\n" << "search (placename state) - displays all info of given place\n" << "same (placename) - displays all places with that name\n" << "quit - exit the program\n";

	while (true)
	{
		string input;
		cin >> input;
		string placename;
		if(input == "quit")
		{
			cout << "Goodbye!\n"; 
			break; 
		}
		if(input == "search")
		{       
    		  cout << "Placename? \n";
	       	  cin >> placename;  
		  int pos = hvalue(placename);       
	  	  int len = length(arr[pos]);      
		  city * found = search(placename, arr[pos]);
		  cin.ignore();            
		  string state;     
		  getline(cin, state);            
		  city * found_st = search(state, arr[pos]);
		  if (found_st != NULL)          
			  cout << found_st->code <<"" << found_st->state << " " << found_st->name << " " << found_st->population << " "<< found_st->area << " " << found_st->latitude << " " << found_st->longitude << " " << found_st->intersection << " " << found_st-> distance <<"\n";
     		}
		if(input == "same")
		{ 
		  cin.ignore();
		  getline(cin, placename);       
		  int pos = hvalue(placename);       
		  int len = length(arr[pos]);      
		  city * found = search(placename, arr[pos]);
		  if (found != NULL)   
			print(arr[pos]);        
		} 
	}    
  	return 0;
}
}
