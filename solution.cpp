#include <iostream>
#include <string>
#include <map>
#include <set>
#include <exception>
#include <iomanip>
using namespace std;

// Реализуйте функции и методы классов и при необходимости добавьте свои
struct Day{
	int value;
	explicit Day(int new_value) {
		value = new_value;
	}
};
struct Month{
	int value;
	explicit Month(int new_value) {
		value = new_value;
	}
};
struct Year{
	int value;
	explicit Year(int new_value) {
		value = new_value;
	}
};
class Date {
public:
	Date(Year new_year, Month new_month, Day new_day) {
		year = new_year.value;
		if(new_month.value > 12 || new_month.value < 1) {
			throw domain_error("Month value is invalid: " + to_string(new_month.value));
		}
		month = new_month.value;
		if(new_day.value > 31 || new_day.value < 1) {
			throw domain_error("Day value is invalid: " + to_string(new_day.value));
		}
		day = new_day.value;
	}
  int GetYear() const{
	  return year;
  }
  int GetMonth() const{
	 return month;
  }
  int GetDay() const{
	  return day;
  }
private:
  int year;
  int month;
  int day;
};

bool operator<(const Date& lhs, const Date& rhs) {
	if(lhs.GetYear() == rhs.GetYear()) {
		if(lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() < rhs.GetDay();
		} else {
			return lhs.GetMonth() < rhs.GetMonth();
		}
	} else {
		return lhs.GetYear() < rhs.GetYear();
	}
}

void PrintDate(const Date& date) {
	cout << setw(4) << setfill('0') << date.GetYear() << "-" << setw(2) << setfill('0') << date.GetMonth() << "-" << setw(2) << setfill('0') << date.GetDay();
}

void EnsureNextSymbolAndSkip(stringstream& stream) {
	if(stream.peek() != '-') {
		throw domain_error("Wrong date format: ");
	}
	stream.ignore(1);
	if(stream.peek() == EOF) {
		throw domain_error("Wrong date format: ");
	}
}

class Database {
public:
  void AddEvent(const Date& date, const string& event) {
	 db[date].insert(event);
  }
  bool DeleteEvent(const Date& date, const string& event) {
	  if(db.count(date) > 0) {
		  if(db[date].count(event) > 0) {
			  db[date].erase(event);
			  return true;
		  }
	  }
	  return false;
  }
  int  DeleteDate(const Date& date) {
	  int value = 0;
	  if(db.count(date) > 0) {
		  value = db[date].size();
		  db.erase(date);
	  }

	  return value;
  }

  void Find(const Date& date) const {
	  if(db.count(date) > 0) {
		  set<string> event = db.at(date);

			  for(const auto& item : event) {
				  cout << item << endl;
			  }

	  }
  }

  void Print() const{
	  for(const auto& item : db) {
		  for(const auto& event : item.second) {
			  PrintDate(item.first);
			  cout << ' ' << event << endl;
		  }
	  }
  }
private:
  map<Date, set<string>> db;
};
//Возвращаем строку если в потоке пробел, разбиваем полученную комманду на строки
string StreamString(stringstream& stream) {
	string str;
	  if(stream.peek() == ' ') {
			  stream.ignore(1);
			  stream >> str;
		  }
	  return str;
}
//Преобразуем строку в дату
Date parseDate(const string& str) {

	int year = 0;
	int month = 1;
	int day = 1;
	Date date(Year{year}, Month{month}, Day{day});
	stringstream input(str);
	try {
		input >> year;
		EnsureNextSymbolAndSkip(input);
		input >> month;
		EnsureNextSymbolAndSkip(input);
		input >> day;

		//char EOF;
		//input >> EOF;
		if(input.peek() != EOF) {
			throw domain_error("Wrong date format: ");
		}

	} catch(const domain_error& de) {
		cout << de.what() << str << endl;
		exit(0);
	}

	return Date(Year{year}, Month{month}, Day{day});


	/*
	int year, month, day;
	char def_1, def_2;
	stringstream input(str);
	input >> year >> def_1 >> month >> def_2 >> day;
	if(input.peek() != EOF || !(input >> year >> def_1 >> month >> def_2 >> day)) {
		throw domain_error("Wrong date format: " + str);
	}
	return Date(Year{year}, Month{month}, Day{day});
	*/
}

int main() {
  Database db;
  string command;
  while (getline(cin, command)) {

	  stringstream stream(command);
	  string str_1, str_2, str_3; // str_1 - command, str_2 - date, str_3 - event
	  stream >> str_1;

	  str_2 = StreamString(stream);
	  Date date(Year{0}, Month{1}, Day{1});
	  if(!str_2.empty()) {
		  try {
			  date = parseDate(str_2);

		   } catch (domain_error& de){
		 	  cout << de.what() << endl;
		 	  exit(0);
		   }

	  }
	  str_3 = StreamString(stream);
	  if(str_1 == "Print") {
		  db.Print();
	  } else if(str_1 == "Add") {

		  db.AddEvent(date, str_3);
	  } else if(str_1 == "Del") {
		 // cout << str_3.empty() << str_3 << endl;

		  if(!str_3.empty()) {

			  if(db.DeleteEvent(date, str_3)) {
				  cout << "Deleted successfully" << endl;
			  } else {
				  cout << "Event not found" << endl;
			  }
		  } else {

			  cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
		  }

	  } else if(str_1 == "Find") {
		  db.Find(date);
	  } else if(str_1 == "") {
		  continue;

	  } else {
		  cout << "Unknown command: " << str_1 << endl;
	  }

    // Считайте команды с потока ввода и обработайте каждую
  }

  return 0;
}
