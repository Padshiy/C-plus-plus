#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

//Наконец, вам нужно реализовать возможность использовать объекты класса Rational в качестве элементов контейнера set и ключей в контейнере map.

class Rational {
public:
  Rational() {
	num = 0;
	den = 1;
  };

  Rational(int numerator, int denominator){
	  if (numerator == 0) {
		  num = numerator;
		  den = 1;
	  } else {

		  if(denominator < 0 && numerator < 0) {
			  numerator = -numerator;
			  denominator = -denominator;
			  int delitel = Delitel(numerator, denominator);
			  num = (numerator / delitel);
			  den = (denominator / delitel);


		  } else if(denominator < 0 && numerator > 0){

			  denominator = -denominator;
			  int delitel = Delitel(numerator, denominator);

			  num = -(numerator / delitel);
			  den = denominator / delitel;

		  } else if (denominator > 0 && numerator < 0){
			  numerator = -numerator;
			  int delitel = Delitel(numerator, denominator);
			  num = -(numerator / delitel);
			  den = denominator / delitel;
		  } else {
			  int delitel = Delitel(numerator, denominator);
			  num = numerator / delitel;
			  den = denominator / delitel;
		  }
	  }


  };

  int Numerator() const {
	return num;
  };
  int Denominator() const{
	return den;
  };
private:
  int num;
  int den;
  int Delitel(int a, int b) const {
	  while( (a > 0) && (b > 0) ) {

	  			if ( a > b ) {
	  				a = a % b;
	  			} else {
	  				b = b % a;
	  			}

	  	}
	  return a + b;
  }
};

Rational operator+ (const Rational& lhs, const Rational& rhs) {
	if(lhs.Denominator() == rhs.Denominator()) {
		return Rational(lhs.Numerator() + rhs.Numerator(), lhs.Denominator());
	}
	return Rational(lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
}

bool operator== (const Rational& lhs, const Rational& rhs) {
	if(lhs.Denominator() == rhs.Denominator()) {
			return lhs.Numerator() == rhs.Numerator();
		}
		return lhs.Numerator() * rhs.Denominator() == rhs.Numerator() * lhs.Denominator();
}

Rational operator- (const Rational& lhs, const Rational& rhs) {
	if(lhs.Denominator() == rhs.Denominator()) {
		return Rational(lhs.Numerator() - rhs.Numerator(), lhs.Denominator());
	}

	return Rational(lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator* (const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator/ (const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}

istream& operator>>(istream& stream, Rational& r) {
	if (stream.tellg() == -1) {
	   return stream;
	}
	if(stream) {
		int num = 0;
		int den = 1;
		stream >> num;
		stream.ignore(1);
		//if(stream >> den) {
			stream >> den;
			r = Rational(num, den);
		//}
	}
	return stream;
}

ostream& operator<<(ostream& stream, const Rational& r) {
	stream << r.Numerator() << "/" << r.Denominator();
	return stream;
}

bool operator < (const Rational& lhs, const Rational& rhs) {
	if(lhs.Denominator() == rhs.Denominator()) {
		return lhs.Numerator() < rhs.Numerator();
	}
	return lhs.Numerator() * rhs.Denominator() < rhs.Numerator() * lhs.Denominator();
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
	return 0;
}
