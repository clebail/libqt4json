/**
 * \file libqt4json.h
 * \author Corentin Le Bail
 * \date 2013
 * \brief Header file for class libqt4json::CJson
 */
//------------------------------------------------------------------------------
#ifndef __LIBQT4JSON_H__
#define __LIBQT4JSON_H__
//------------------------------------------------------------------------------
#include <QObject>
#include <QString>
#include <QVariant>
//------------------------------------------------------------------------------
/**
 * \namespace libqt4json
 */ 
namespace libqt4json {
	//------------------------------------------------------------------------------
	/**
	 * \class CJson libqt4json.h "libqt4json.h"
	 * \brief Class for serialize / deserialize json
	 */
	class CJson {
		public:
			/**
			 * \fn QString toString(QVariant variant)
			 * \brief Serializator
			 * \param[in] variant QVariant object to serialize
			 * \return A Json String
			 */
			QString toString(QVariant variant);
			/**
			 * \fn QVariant fromString(QString json)
			 * \brief Deserializator
			 * \param[in] json Json string to deserialize
			 * \param[out] ok Set to true if no error occur, false otherwise
			 * \return A QVariant object that represents Json
			 */
			QVariant fromString(QString json, bool& ok);
			/**
			 * \fn QString getLastError(void)
			 * \return Last parsing error;
			 */
			QString getLastError(void);
		private:
			QString lastError;
		
			QString variantToString(QVariant variant, bool& simpleType);
			QString objectStarToString(QVariant variant);
			QString listToString(QVariant variant);
			QString mapToString(QVariant variant);
			QString protect(QString str);
	};
	//------------------------------------------------------------------------------
} //namespace
//------------------------------------------------------------------------------
#endif //_LIBQT4JSON_H__
//------------------------------------------------------------------------------
/**
 * \mainpage
 * Below is an example of how to use libqt4json<br />
 * \code{.cpp}
//------------------------------------------------------------------------------
#include <QObject>
#include <QDate>
#include <iostream>
#include <libqt4json.h>
//------------------------------------------------------------------------------
using libqt4json::CJson;
using namespace std;
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------ 
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
 //------------------------------------------------------------------------------
 int main(int argc, char **argv) {
	CJson *json=new CJson();
	CPerson *parent1=new CPerson("Dad", new CBirthDay(QDate::fromString("07/04/1977", "dd/MM/yyyy")));
	CPerson *parent2=new CPerson("Mum", new CBirthDay(QDate::fromString("15/07/1977", "dd/MM/yyyy")));
	CPerson *child1=new CPerson("Cindy", new CBirthDay(QDate::fromString("01/10/2011", "dd/MM/yyyy")));
	QVariantMap family;
	QVariantList parents;
	QVariantList childs;
	
	parents.append(QVariant::fromValue((QObject *)parent1));
	parents.append(QVariant::fromValue((QObject *)parent2));
	
	childs.append(QVariant::fromValue((QObject *)child1));
	
	family.insert("parents", QVariant(parents));
	family.insert("childs", QVariant(childs));
	
	QString sJson=json->toString(QVariant(family));
	
	cout << QObject::tr("Generated json").toStdString() << ":" << endl;
	cout << sJson.toStdString();
	cout << endl;
	
	return 0;
}
//------------------------------------------------------------------------------
 * \endcode
 * This will produce : 
 * \code{.json}
{
    "childs": [
        {
            "name": "Cindy",
            "age": 1,
            "birthDay": {
                "day": 1,
                "monthName": "octobre",
                "year": 2011
            }
        }
    ],
    "parents": [
        {
            "name": "Dad",
            "age": 35,
            "birthDay": {
                "day": 7,
                "monthName": "avril",
                "year": 1977
            }
        },
        {
            "name": "Mum",
            "age": 35,
            "birthDay": {
                "day": 15,
                "monthName": "juillet",
                "year": 1977
            }
        }
    ]
}
 * \endcode
 */
