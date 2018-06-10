#ifndef _title_h__
#define _title_h__

#include "book.hpp"
#include <cstring>

class TitleComparator
{
  public:
    bool operator( ) (const Book::SecondaryKey & key1, 
                      const Book::SecondaryKey & key2) const
    {
      	string title1 = key1.getTitle();
		string title2 = key2.getTitle();
		for(size_t i = 0; i < title1.size(); ++i){
			title1[i] = tolower(title1[i]);
		}
		for(size_t i = 0; i < title2.size(); ++i){
			title2[i] = tolower(title2[i]);
		}
  		if(title1 < title2){
  			return true;
  		}
  		else if(title1 > title2){
  			return false;
  		}
  		else{
  			string author1 = key1.getAuthor();
  			string author2 = key2.getAuthor();
  			for(size_t i = 0; i < author1.size(); ++i){
			author1[i] = tolower(author1[i]);
			}
			for(size_t i = 0; i < author2.size(); ++i){
				author2[i] = tolower(author2[i]);
			}
			if(author1 < author2){
				return true;
			}
			else{
				return false;
			}
  		}
    }

};

#endif
