#include <QObject>
#include <QDate>

class CBirthDay : public QObject {
	Q_OBJECT
	Q_PROPERTY(int day READ getDay)
	Q_PROPERTY(QString monthName READ getMonthName);
	Q_PROPERTY(int year READ getYear);
	public:
		CBirthDay(QDate date) { this->date=date; }
		int getDay(void) { return date.day(); }
		QString getMonthName(void) { return QDate::longMonthName(date.month()); }
		int getMonth(void) { return date.month(); }
		int getYear(void) { return date.year(); }
	private:
		QDate date;
};

class CPerson : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString name READ getName)
	Q_PROPERTY(int age READ getAge);
	Q_PROPERTY(QObject* birthDay READ getBirthDay);
	public:
		CPerson(QString name, CBirthDay *birthDay) { this->name=name; this->birthDay=birthDay; }
		QString getName(void) { return name; }
		int getAge(void) { 
			QDate curDate=QDate::currentDate();
			int curYear=curDate.year();
			int curMonth=curDate.month();
			int curDay=curDate.day();
			int age=curYear-birthDay->getYear();
			if(curMonth < birthDay->getMonth() || (curMonth == birthDay->getMonth() && curDay < birthDay->getDay())) {
				return age-1;
			}
			return age;
		}
		CBirthDay *getBirthDay(void) { return birthDay; } 
	private:
		QString name;
		CBirthDay *birthDay;
		
};
