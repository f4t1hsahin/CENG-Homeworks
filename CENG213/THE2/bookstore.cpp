#include "bookstore.hpp"

BookStore::BookStore( ) //implemented, do not change
{
}

void
BookStore::insert(const Book & book)
{
  Book* new_book = new Book(book.getISBN(), book.getTitle(), book.getAuthor(),"",0,0);
  *new_book = book;
  Book::SecondaryKey *skey = new Book::SecondaryKey(*new_book);
  primaryIndex.insert(book.getISBN(),*new_book);
  //cout <<  "BOOK   "<<*primaryIndex.find(book.getISBN()) << endl;
  secondaryIndex.insert(*skey, &(*primaryIndex.find(book.getISBN())) );
  ternaryIndex.insert(*skey, &(*primaryIndex.find(book.getISBN())) );
  /*cout << "SIZE  " << secondaryIndex.size() << endl;
  cout << "LISTT" << endl;
  printSecondarySorted();
  cout << "ASDASD" << endl;*/
  delete skey;
  delete new_book;

}

void
BookStore::remove(const std::string & isbn)
{
  BSTP::Iterator it;
  it = primaryIndex.find(isbn);
  if(it == primaryIndex.end())
    return;
  Book::SecondaryKey *skey = new Book::SecondaryKey(*it);
  secondaryIndex.remove(*skey);
  ternaryIndex.remove(*skey);
  primaryIndex.remove(isbn);
  delete skey;
}

void
BookStore::remove(const std::string & title,
                  const std::string & author)
{
  using namespace std;
  SKey *skey = new SKey(title, author);
  BSTT::Iterator it = ternaryIndex.find(*skey);
  string _isbn = (*it) -> getISBN(); 
  secondaryIndex.remove(*skey);
  ternaryIndex.remove(*skey);
  primaryIndex.remove(_isbn);
  delete skey;
  
  /*BSTP::Iterator it;
  string token1 = title;
  string token2 = author;
  for(size_t i = 0; i < token1.size(); ++i){
      token1[i] = tolower(token1[i]);
    }
    for(size_t i = 0; i < token2.size(); ++i){
      token2[i] = tolower(token2[i]);
    }
    //std::cout << "TITLE  " << token1 << "AUTHOR  " << token2 << std::endl;
  for(it = primaryIndex.begin(); it != primaryIndex.end(); ++it){
    string _title = (*it).getTitle();
    string _author = (*it).getAuthor();
    for(size_t i = 0; i < _title.size(); ++i){
      _title[i] = tolower(_title[i]);
    }
    for(size_t i = 0; i < _author.size(); ++i){
      _author[i] = tolower(_author[i]);
    }
    std::cout << "TITLE  " << _title << "AUTHOR  " << _author << std::endl;
    std::cout << "TITLE  " << token1 << "AUTHOR  " << token2 << std::endl;
    std::cout << (_title == title and _author == author) << std::endl;
    if(_title == token1 and _author == token2){
      string _isbn = (*it).getISBN();
      Book::SecondaryKey *skey = new Book::SecondaryKey(*it);
      secondaryIndex.remove(*skey);
      ternaryIndex.remove(*skey);
      primaryIndex.remove(_isbn);
      delete skey;
      break;
    }
  }*/

}

void
BookStore::removeAllBooksWithTitle(const std::string & title)
{
  using namespace std;
  BSTT::Iterator it;
  string _title = title;
  bool flag = false;
  for(size_t i = 0; i < _title.size(); ++i){
      _title[i] = tolower(_title[i]);
  }
    //cout << "SILINECEK TITLE  " << _title << endl;
    //primaryIndex.print(std::cout);
  //std::cout << _title << std::endl;
  for(it = ternaryIndex.begin(); it != ternaryIndex.end(); ++it){
    if(flag == true){
      flag = false;
      it = ternaryIndex.begin();
    }
    string token = (*it) -> getTitle();
    //std::cout << "xx" << token << std::endl;
    for(size_t i = 0; i < token.size(); ++i){
      token[i] = tolower(token[i]);
    }
    //std::cout << "TOKEN=    " << token << std::endl;
    if(_title == token){
      flag = true;
      //cout << "TITLE  "<< _title << endl;
      //cout << "TOKEN  "<< token << endl;
      string _isbn = (*it) -> getISBN();
      //cout <<"ISBN   " <<  _isbn << endl;
      Book::SecondaryKey *skey = new Book::SecondaryKey(*(*it));
      secondaryIndex.remove(*skey);
      ternaryIndex.remove(*skey);
      primaryIndex.remove(_isbn);
      delete skey;
    }
  }
  
  for(it = ternaryIndex.begin(); it != ternaryIndex.end();){
    string token = (*it) -> getTitle();
    //std::cout << "xx" << token << std::endl;
    for(size_t i = 0; i < token.size(); ++i){
      token[i] = tolower(token[i]);
    }
    //std::cout << "TOKEN=    " << token << std::endl;
    if(_title == token){
        removeAllBooksWithTitle(_title);
        it = ternaryIndex.begin();
        continue;
    }
    ++it;
  }
  
     /*for(it = ternaryIndex.begin(); it != ternaryIndex.end(); ++it){
    string token = (*it) -> getTitle();
    //std::cout << "xx" << token << std::endl;
    for(size_t i = 0; i < token.size(); ++i){
      token[i] = tolower(token[i]);
    }
    //std::cout << "xxqw" << token << std::endl;
    if(_title == token){
      //cout << "TITLE  "<< _title << endl;
      //cout << "TOKEN  "<< token << endl;
      string _isbn = (*it) -> getISBN();
      Book::SecondaryKey *skey = new Book::SecondaryKey(*(*it));
      
      secondaryIndex.remove(*skey);
      ternaryIndex.remove(*skey);
      primaryIndex.remove(_isbn);
      delete skey;
      it = ternaryIndex.begin();
    }

  }
  
    for(it = ternaryIndex.begin(); it != ternaryIndex.end(); ++it){
        string token = (*it) -> getTitle();
        //std::cout << "xx" << token << std::endl;
        for(size_t i = 0; i < token.size(); ++i){
          token[i] = tolower(token[i]);
        }
        //std::cout << "xxqw" << token << std::endl;
        if(_title == token){
          //cout << "TITLE  "<< _title << endl;
          //cout << "TOKEN  "<< token << endl;
          string _isbn = (*it) -> getISBN();
          Book::SecondaryKey *skey = new Book::SecondaryKey(*(*it));
          
          secondaryIndex.remove(*skey);
          ternaryIndex.remove(*skey);
          primaryIndex.remove(_isbn);
          delete skey;
          it = ternaryIndex.begin();
        }
  }*/
}


void
BookStore::makeAvailable(const std::string & isbn)
{
  BSTP::Iterator it = primaryIndex.find(isbn);
  (*it).setAvailable();
}

void
BookStore::makeUnavailable(const std::string & title,
                           const std::string & author)
{
  SKey skey(title,author);
  BSTT::Iterator it = ternaryIndex.find(skey);
  if(it == ternaryIndex.end()) return;
  (*it) -> setUnavailable();
  /*BSTP::Iterator it;
  string _title = title;
  string _author = author;
  for(size_t i = 0; i < _title.size(); ++i){
      _title[i] = tolower(_title[i]);
    }
  for(size_t i = 0; i < _author.size(); ++i){
      _author[i] = tolower(_author[i]);
    }
  for(it = primaryIndex.begin(); it != primaryIndex.end(); ++it){
    string token1 = (*it).getTitle();
    string token2 = (*it).getAuthor();
    for(size_t i = 0; i < token1.size(); ++i){
      token1[i] = tolower(token1[i]);
    }
    for(size_t i = 0; i < token2.size(); ++i){
      token2[i] = tolower(token2[i]);
    }
    if(_title == token1 and _author == token2){
      (*it).setUnavailable();
    }
  }*/

  
}

void
BookStore::updatePublisher(const std::string & author, 
                           const std::string & publisher)
{
  using namespace std;
  BSTP::Iterator it;
  string _author = author;
  for(size_t i = 0; i < _author.size(); ++i){
      _author[i] = tolower(_author[i]);
    }
  for(it = primaryIndex.begin(); it != primaryIndex.end(); ++it){
    string token = (*it).getAuthor();
    for(size_t i = 0; i < token.size(); ++i){
      token[i] = tolower(token[i]);
    }
    if(_author == token){
      (*it).setPublisher(publisher);
    }
  }
}

void
BookStore::printBooksWithISBN(const std::string & isbn1,
                              const std::string & isbn2,
                              unsigned short since) const
{
  using namespace std;
  BSTP::Iterator it;
  for(it = primaryIndex.begin(); it != primaryIndex.end(); ++it){
    string _isbn = (*it).getISBN();
    unsigned short _year = (*it).getYear();
    if(_isbn >= isbn1 and _isbn <= isbn2 and _year >= since){
      std::cout << *it << std::endl;
    }
    if(_isbn > isbn2)
        break;
  }

}

void
BookStore::printBooksOfAuthor(const std::string & author,
                              const std::string & first,
                              const std::string & last) const
{
  using namespace std;
  BSTT::Iterator it;
  string _author = author;
  string _first = first;
  string _last = last;
  for(size_t i = 0; i < _first.size(); ++i){
      _first[i] = tolower(_first[i]);
    }
  for(size_t i = 0; i < _last.size(); ++i){
      _last[i] = tolower(_last[i]);
    }
    
  //std::cout << first <<"    " << last << std::endl;
  for(size_t i = 0; i < _author.size(); ++i){
      _author[i] = tolower(_author[i]);
  }
  for(it = ternaryIndex.begin(); it != ternaryIndex.end(); ++it){
    string token = (*it) -> getAuthor();
    for(size_t i = 0; i < token.size(); ++i){
      token[i] = tolower(token[i]);
    }
    string _title = (*it) -> getTitle();
    for(size_t i = 0; i < _title.size(); ++i){
      _title[i] = tolower(_title[i]);
    }
    //std::cout << "AUTHOR  " << _author << "TOKEN  " << token << std::endl;
    //std::cout << (_author == token) << std::endl;
    if(_author == token){
      if(_title >= _first and _title <= _last)
        std::cout << *(*it) << std::endl;
    }

  }

}

void //implemented, do not change
BookStore::printPrimarySorted( ) const
{
  BSTP::Iterator it;

  for (it=primaryIndex.begin(); it != primaryIndex.end(); ++it)
  {
    std::cout << *it << std::endl;
  }
}

void //implemented, do not change
BookStore::printSecondarySorted( ) const
{
  BSTS::Iterator it;

  for (it = secondaryIndex.begin(); it != secondaryIndex.end(); ++it)
  {
    std::cout << *(*it) << std::endl;
  }
}

void //implemented, do not change
BookStore::printTernarySorted( ) const
{
  BSTT::Iterator it;

  for (it = ternaryIndex.begin(); it != ternaryIndex.end(); ++it)
  {
    std::cout << *(*it) << std::endl;
  }
}

