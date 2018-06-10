#include "Article.h"
#include <iostream>

/*#############################
#               NOTE!         #
#    Please don't forget to   #
#     check PDF. Fuctions     #
#    may have more detailed   #
#     tasks which are not     #
#       mentioned here.       #
#############################*/

Article::Article( int _size,int h1_, int h2_ )
{    
    /*#############################
    #            TO-DO            #
    # Write a default constructor #
    #   for the Article Class     #
    #############################*/
    int i;
    table_size = _size;
    h1_param = h1_;
    h2_param = h2_;
    n = 0;
    table = new std::pair<std::string, int>[table_size];
    for(i = 0; i < table_size; ++i){
        table[i] = std::pair<std::string, int>(EMPTY_KEY, EMPTY_INDEX);
    }
    //std::cout << i << std::endl;
}

Article::~Article()
{
    /*#############################
    #             TO-DO           #
    #  Write a deconstructor for  #
    #     the Article Class       #
    #############################*/
    delete[] table;
}

int Article::get( std::string key, int nth, std::vector<int> &path ) const
{
    /*#############################################
    #                    TO-DO                    #
    #      Your get function should return        #
    # the original index (index in the text file) #
    #    of the nth 'key' in the hash table.      #
    #    If there is no such a key, return -1     #
    #    If there is, return the original index   #
    #     In both cases, you need to push each    #
    #          visited index while probing        #
    #           that you calculated until         #
    #      finding the key, to the path vector.   #
    #############################################*/
    int index, i = 0, count = 0;
    while(i < table_size){
        index = hash_function(key, i++);
        if(i != 1)
            path.push_back(index);
        if(table[index].first == key){
            if(count == nth - 1)
                return table[index].second;
            count++;
        }
        if(table[index].second == EMPTY_INDEX)
            break;
    }

    
    /*
    index = hash_function(key, i++);
    if(table[index].first == key){
        res = table[index].second;
        count++;
    }
    for(int t = 0; t < table_size; t++){
        if(count > nth)
            break;
        index = hash_function(key, i++);
        //std::cout << "index  "  << index << std::endl;
        if(table[index].first == key){
            res = table[index].second;  
            count++;
        }
        path.push_back(index);
    }*/
    return -1;
}

int Article::insert( std::string key, int original_index )
{
    /*#########################################
    #                 TO-DO                   #
    #      Insert the given key, with the     #
    # original index value (at the text file) #
    #           to the hash table.            #
    #  Return the total number of probes you  #
    #      encountered while inserting.       #
    #########################################*/
    int index, i = 0, tmp1,tmp2 = original_index;
    //std::cout << "keyyy  " << key << std::endl;
    //std::cout << "original_index  " << original_index << std::endl;

    if(getLoadFactor() > MAX_LOAD_FACTOR)
        expand_table();
    while(1){
        index = hash_function(key, i++);
        
        //std::cout << "tmp_indexxx  " << tmp << std::endl;

        //std::cout << "indexxx  " << index << std::endl;
        if(table[index].first == key and table[index].second > original_index){
                tmp1 = table[index].second;
                table[index].second = tmp2;
                tmp2 = tmp1;
        }
        if(table[index].first != EMPTY_KEY)
            break;
    }
    table[index] = std::pair<std::string, int>(key, tmp2);
    n++; 
    return i - 1;
}


int Article::remove( std::string key, int nth )
{
    /*#########################################
    #                  TO-DO                  #
    #      Remove the nth key at the hash     #
    #                  table.                 #
    #  Return the total number of probes you  #
    #      encountered while inserting.       #
    #   If there is no such a key, return -1  #
    #     If there, put a mark to the table   #
    #########################################*/
    int i = 0, index = 0, count = 0, t = 0;
    index = hash_function(key, i++);
    if(table[index].first == key){
        count++;
    }
    //std::cout << table[index].first << std::endl;
    //std::cout << count << "  " << nth << std::endl;
    while(count < nth){
        index = hash_function(key, i++);
        //std::cout << table[index].first << std::endl;
        if(table[index].first == key)
            count++;
        t++;
        if(table[index].second == EMPTY_INDEX)
            break;
    //std::cout << key << "  " << table[index].first << std::endl;

    //std::cout << count << "  " << nth << std::endl;

    }
    if(table[index].first == key){ //found
        table[index].first = EMPTY_KEY;
        table[index].second = MARKED_INDEX;
        n--;
        return t;
    }
    else{
        return -1;
    }
    return 0;
}

double Article::getLoadFactor() const
{
    /*#########################################
    #                TO-DO                    #
    #      Return the load factor of the      #
    #                table                    #
    #########################################*/
    //std::cout << n << std::endl;
    //std::cout << table_size << std::endl;

    return ((double)n)/ table_size;
}

void Article::getAllWordsFromFile( std::string filepath )
{
    /*#########################################
    #                  TO-DO                  #
    #       Parse the words from the file     #
    #      word by word and insert them to    #
    #                hash table.              #
    #   For your own inputs, you can use the  #
    #  'inputify.py' script to fix them to    #
    #            the correct format.          #
    #########################################*/
    std::ifstream file;
    std::string word;
    file.open(filepath.c_str());
    if(!file.good())
        return;
    int index = 1;
    while(file >> word){
        //std::cout << word << "  " << index << std::endl;
        insert(word,index++);
    }
    file.close();
}

void Article::expand_table()
{
    /*#########################################
    #                  TO-DO                  #
    #   Implement the expand table function   #
    #   in order to increase the table size   #
    #   to the very first prime number after  #
    #      the value of (2*table size).       #
    #         Re-hash all the data.           #
    #       Update h2_param accordingly.      #
    #########################################*/
    int temp = table_size;
    n = 0;
    table_size = nextPrimeAfter(2 * table_size);
    h2_param = firstPrimeBefore(table_size);
    std::pair<std::string, int>* tmp = table;
    table = new std::pair<std::string, int>[table_size];
    //std::cout << table_size << "  " << h2_param << std::endl;
    for(int i = 0; i < table_size; ++i){
        table[i] = std::pair<std::string, int>(EMPTY_KEY, EMPTY_INDEX);
    }
    for(int i = 0; i < temp; ++i){
        if(tmp[i].first != EMPTY_KEY){
            insert(tmp[i].first, tmp[i].second);
        }
    }
    delete[] tmp;
}

int Article::hash_function( std::string& key, int i ) const
{
    /*#########################################
    #                TO-DO                    #
    #       Implement the main hashing        #
    #    function. Firstly, convert key to    #
    #    integer as stated in the homework    #
    #      text. Then implement the double    #
    #            hashing function.            #
    #      use convertStrToInt function to    #
    #      convert key to a integer for       #
    #         using it on h1 and h2           #
    #               reminder:                 #
    #            you should return            #
    #    ( h1(keyToInt) + i*h2(keyToınt) )    #
    #            modulo table_size            #
    #########################################*/
    int tmp = convertStrToInt(key);
    return ((h1(tmp) + i * h2(tmp)) % table_size);
}

int Article::popCount(int i) const
{
    int tmp = i;
     tmp = tmp - ((tmp >> 1) & 0x55555555);
     tmp = (tmp & 0x33333333) + ((tmp >> 2) & 0x33333333);
     return (((tmp + (tmp >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}


int Article::h1( int key ) const
{
    /*###############################
    #              TO-DO            #
    #      First Hash function      #
    # Don't forget to use h1_param. #
    ###############################*/
    int tmp = popCount(key);
    return tmp * h1_param;
}

int Article::h2( int key ) const
{
    /*###############################
    #              TO-DO            #
    #     Second Hash function      #
    # Don't forget to use h2_param. #
    ###############################*/

    return (h2_param - (key % h2_param));
}
