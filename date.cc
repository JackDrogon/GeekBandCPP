#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <algorithm>

using namespace std;

// @doc
// year < 0, 公元前
class Date {
private:
	const static int days_[];
public:
	Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}
	inline bool Init();
	inline void Print();

	bool operator < (const Date &rhs) const;
	bool operator > (const Date &rhs) const;
	bool operator == (const Date &rhs) const;

private:
	int year_;
	int month_;
	int day_;
};

const int Date::days_[] = { 0,
	31, 29, 31, 30,
	31, 30, 31, 31,
	30, 31, 30, 31 };

inline bool Date::Init()
{
	if (month_ < 1 || month_ > 12) return false;
	if (day_ < 1 || day_ > days_[month_]) return false;

	int year = abs(year_);
	if (year % 4 || (year % 4 == 0 && year % 400)) return day_ < 29;

	return true;
}

inline void Date::Print()
{
	cout << year_ << "-" << month_ << "-" << day_ << endl;
}

bool Date::operator > (const Date &rhs) const
{
	int l_date[3] = {year_, month_, day_};
	int r_date[3] = {rhs.year_, rhs.month_, rhs.day_};

	for (int i = 0; i < 3; ++i) {
		if (l_date[i] > r_date[i]) {
			return true;
		} else if (l_date[i] < r_date[i]) {
			return false;
		}
	}

	// @doc lhs == rhs
	return false;
}

bool Date::operator < (const Date &rhs) const
{
	return ! (*this > rhs || *this == rhs);
}

bool Date::operator == (const Date &rhs) const
{
	return year_ == rhs.year_ && month_ == rhs.month_ && day_ == rhs.day_;
}

vector<Date> create_points()
{
	vector<Date> dates;
	Date *date;
	std::random_device r;
	std::default_random_engine e(r());
	std::uniform_int_distribution<int> year_dis(1, 2016), month_dis(1, 12), day_dis(1, 31);
	int year, month, day;

	for (int i = 0; i < 10; ++i) {
		while (true) {
			year = year_dis(e), month = month_dis(e), day = day_dis(e);
			date = new Date(year, month, day);
			if (date->Init()) {
				dates.push_back(*date);
				break;
			} else {
				delete date;
			}
		}
	}

	assert(dates.size() == 10);

	return dates;
}

int main()
{
	vector<Date> dates = create_points();

	sort(dates.begin(), dates.end());

	for (auto &date : dates) {
		date.Print();
	}
	
	return 0;
}
