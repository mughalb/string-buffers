#include <iostream>

using namespace std;

class StringBuffer{
    private:
        char* _strbuf;                                   //buffer to store the original string
        int _length;     
    
    public:
    StringBuffer(){
        _strbuf = NULL;
        _length = NULL;
    } //default constructor

    ~StringBuffer(){
        free(_strbuf);
        _strbuf = NULL;
        _length = NULL;

    }                //destructor; would delete the allocated buffer

    StringBuffer(const StringBuffer& E){
        _length = E.length();
        _strbuf = (char*) malloc (sizeof(char) * _length);
        for(int i=0; i<_length; i++){
            *(_strbuf + i) = E.charAt(i);

        }

    }              //constructor for shallow copying

    StringBuffer(char* chars,int length){
        _strbuf = (char*) malloc (sizeof(char) * length);
        _length = length;

        for(int i=0; i<length; i++){

            *(_strbuf + i) = chars[i];
        }
    }   //constructor to convert a char* to StringBuffer

    char charAt(int index) const{
        return *(_strbuf + index);
    }   //returns the character at the passed index

    int length() const{
        return _length;

    }                            //returns the length of the buffer

    void reserve(int length){
        free(_strbuf);
        _strbuf = NULL;
        _length = NULL;
        _strbuf = (char*) malloc(sizeof(char) * length);
        _length = length;
    }                             //allocates memory for the string, according to the passed character length

    void append( char c){
         _length++;
        _strbuf = (char*) realloc(_strbuf,sizeof(char) * (_length));
        *(_strbuf+(_length-1)) = c;
    }                          //appends a single character at the end
                           

};


int main(){
    StringBuffer Name("mughal",6);
    StringBuffer Name2(Name);
	Name2.append('t');
	Name2.append('a');
	Name2.append('l');
	Name2.append('h');
	Name2.append('a');

    cout << "Length: " << Name2.length() << " Letter:" << Name2.charAt(6) << '\n';

    return 0;
}