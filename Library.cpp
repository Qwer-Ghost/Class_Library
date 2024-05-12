#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Book {
  string title;
  string author;
  int publication_year;
  bool status;
public:
  Book() {
    this->title = "";
    this->author = "";
    this->publication_year = 0;
    this->status = false;
  }
  Book(const string title, const string author, const int publication_year) {
    this->title = title;
    this->author = author;
    this->publication_year = publication_year;
    this->status = false;
  } 

  string GetTitle() {
    return title;
  }
  void SetTitle(const string title) {
    this->title = title;
  }
  string GetAuthor() {
    return author;
  }
  void SetAuthor(const string author) {
    this->author = author;
  }
  int GetPublication_year() {
    return publication_year;
  }
  void SetPublication_year(int publication_year) {
    this->publication_year = publication_year;
  }
  bool GetStatus() {
    return status;
  }
  void SetStatus(bool status) {
    this->status = status;
  }

  void issue() {
    this->status = false;
  }
  void return_book() {
    this->status = true;
  }

  void Print() {
    cout << "Книга:";
    cout << "\n\tНазва: " << title;
    cout << "\n\tАвтор: " << author;
    cout << "\n\tРiк видання: " << publication_year;
    cout << "\n\tСтатус: ";if (status)cout << "в наявностi"; else cout << "в наявностi не має";
    cout << "\n\n";
  }
  ~Book() {

  }
};
class Reader {
  string name;
  int age;
  vector<Book> read_book;
public:
  Reader() {
    this->name = "";
    this->age = 0;
  }
  Reader(const string name, int age) {
    this->name = name;
    this->age = age;
  }

  string GetName() {
    return name;
  }
  void SetName(const string name) {
    this->name = name;
  }
  int GetAge() {
    return age;
  }
  void SetAge(int age) {
    this->age = age;
  }
  vector<Book> GetRead_book() {
    return read_book;
  }
  void SetRead_book(vector<Book> read_book) {
    for (int i = 0; i < read_book.size(); i++)
      read_book[i].issue();
    this->read_book = read_book;

  }

  void borrow_book(Book &book){
    if (book.GetStatus()){
      book.issue();
      this->read_book.push_back(book);
    }
  }
  void return_book(Book& book) {
    
    for (int i = 0; i < read_book.size(); i++) {
      if (book.GetTitle() == read_book[i].GetTitle() && book.GetAuthor() == read_book[i].GetAuthor() && book.GetPublication_year() == read_book[i].GetPublication_year() && book.GetStatus() == read_book[i].GetStatus()) {
        read_book.erase(read_book.begin() + i);
        break;
      }
    }
    book.return_book();
  }

  void Print() {
    cout << "Читач:";
    cout << "\n\tIм'я: " << name;
    cout << "\n\tВiк: " << age;
    cout << "\n\tСписок книг, якi читач взяв у бiблiотецi: ";
    for (int i = 0; i < read_book.size(); i++) {
      cout << read_book[i].GetTitle(); if (i + 1 == read_book.size())cout << "."; else cout << ", ";
    }
    cout << "\n\n";
  }

  ~Reader() {

  }
};
class Library {
  vector<Book>books;
  vector<Reader>readers;
public:
  void add_book(Book &book) {
    book.return_book();
    books.push_back(book);
  }
  void add_reader(Reader &reader) {
    readers.push_back(reader);
  }
  void issue_book(Reader& reader, Book& book) {
    for (int i = 0; i < books.size(); i++) {
      if (book.GetTitle() == books[i].GetTitle() && book.GetAuthor() == books[i].GetAuthor() && book.GetPublication_year() == books[i].GetPublication_year() && book.GetStatus() == books[i].GetStatus()) {
        books.erase(books.begin() + i);
        break;
      }
    }
    reader.borrow_book(book);
  }
  void return_book(Reader& reader, Book& book) {
    
    reader.return_book(book);
    book.return_book();
    books.push_back(book);
  }
  void Print() {
    cout << "Бiблiотека:";
    cout << "\n\tCписок всiх книг у бiблiотецi: ";
    for (int i = 0; i < books.size(); i++) {
      cout << "\"" << books[i].GetTitle() << "\""; if (i + 1 == books.size())cout << "."; else cout << ", ";
    }
    cout << endl;
    cout << "\n\tCписок всiх читачiв: ";
    for (int i = 0; i < readers.size(); i++) {
      cout << readers[i].GetName(); if (i + 1 == readers.size())cout << "."; else cout << ", ";
    }
    cout << "\n\n";
  }
  ~Library() {

  }
};
int main() {
  setlocale(LC_ALL, "ukr");
  Book a("Кохання в мозку", "Ali Hazelwood", 2024), b("Секрет служницi", "Vivat", 2024), c("Двiр шипiв i троянд Двiр срiбного полум'я", "Sarah J. Maas", 2023);
  Reader q("Людисько", 15),r("Людя",33); 
  Library l;
  l.add_book(a);q.borrow_book(a);
  l.add_book(b); l.add_book(c); l.add_reader(r); l.add_reader(q);
  a.Print(); b.Print(); c.Print();
  q.Print(); r.Print(); l.Print();
  q.return_book(a);
  l.issue_book(r, b);
  r.Print();
  l.return_book(r, b);
  q.Print(); r.Print(); l.Print();
  return 0;
}
