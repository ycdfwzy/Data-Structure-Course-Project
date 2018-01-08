#include "Post.h"

typedef long long LL;

Post::Post(wCharString & webadd_) : webadd(webadd_) {}

Post::Post(wCharString& webadd_, wCharString& ctg1_, wCharString& ctg2_, wCharString& title_, wCharString& cont_, wCharString& author_, wCharString& date_, wCharString& type_):
		webadd(webadd_), ctg1(ctg1_), ctg2(ctg2_), title(title_), cont(cont_), author(author_), date(date_), type(type_){}

Post::Post(const Post &c){
	webadd = c.webadd;
	ctg1 = c.ctg1;
	ctg2 = c.ctg2;
	title = c.title;
	cont = c.cont;
	author = c.author;
	date = c.date;
	type = c.type;
	part = c.part;
}

Post::~Post(){}

wCharString Post::getwebadd() const { return webadd;}
void Post::setwebadd(const wCharString &c) { webadd = c; }
void Post::setctg1(const wCharString &c) { ctg1 = c; }
void Post::setctg2(const wCharString &c) { ctg2 = c; }
void Post::settitle(const wCharString &c) { title = c; }
void Post::setcont(const wCharString &c) { cont = c; }
void Post::setauthor(const wCharString &c) { author = c; }
void Post::setdate(const wCharString &c) { date = c; }
void Post::settype(const wCharString &c) { type = c; }

void Post::divideWords(int type) {
	/*use hash table*/
	if (type == 0) {
		//std::wcout << "divideWords" << std::endl;
		Dictionary::getSingle()->divide(title, part);
		Dictionary::getSingle()->divide(cont, part);
		/*std::wcout << title << std::endl;
		std::wcout << cont << std::endl;
		std::wcout << *this << std::endl;*/
	}
	/*use Aho-Corasick automation*/
	else {
		Dictionary_AC_Automation::getsingle()->divide(title, part);
		Dictionary_AC_Automation::getsingle()->divide(cont, part);
	}
}

Post & Post::operator=(const Post &c) {
	webadd = c.webadd;
	ctg1 = c.ctg1;
	ctg2 = c.ctg2;
	title = c.title;
	cont = c.cont;
	author = c.author;
	date = c.date;
	type = c.type;
	part = c.part;
	return *this;
}

std::wostream& operator<<(std::wostream &os, Post &c) {
	os << ",\"" << c.webadd << "\"";
	os << ",\"" << c.ctg1 << "\"";
	os << ",\"" << c.ctg2 << "\"";
	os << ",\"" << c.title << "\"";
	os << ",\"" << c.cont << "\"";
	os << ",\"" << c.author << "\"";
	os << ",\"" << c.date << "\"";
	os << ",\"" << c.type << "\"";
	os << ",\"" << c.part << "\"";
	return os;
}