#include <cstdlib>
#include <iostream>
#include <memory>
#include <cstring>


using namespace std;

class StringBuffer{
public :
    StringBuffer();
    ~StringBuffer();
    StringBuffer(const StringBuffer&);
    StringBuffer(char*,int);

    char charAt(int) const;
    int length() const;
    void smartCopy(char*,int);
    void smartCopy(StringBuffer*);
    void revSmartCopy(char* newString);
    void reserve(int);
    void append(char);
    int _refcount;
private:
    char* _strbuf;
    int _length;
    
};

StringBuffer::StringBuffer() {
    this->_strbuf = 0;
    this->_length = 0;
    this->_refcount = 1;
}
//destructor

StringBuffer::~StringBuffer() {
    _strbuf = NULL;
    delete[] this->_strbuf;
}

//copy a const StringBuffer into this string

StringBuffer::StringBuffer(const StringBuffer& newString) {
    this->_strbuf = new char[newString.length()];
    this->_length = newString.length();
    //copy the passed string into internal buffer
    this->smartCopy(newString._strbuf, _length);
}

//copy a char* into your string

StringBuffer::StringBuffer(char* newString, int length) {
    _length = length;
    _strbuf = NULL;
    delete[] _strbuf;
    _strbuf = new char[length];
    _strbuf = newString;

    //Should I delete the string passed by the user?
    //delete[] newString;

}

//make a smart copy of the StringBuffer into the callee StringBuffer

void StringBuffer::smartCopy(StringBuffer* newString) {
    int shorterLength = 0;
    (this->_length < newString->_length) ? shorterLength = this->_length : shorterLength = newString->_length;
    int it = 0;
    while (it < shorterLength) {
        *_strbuf++ = *(newString->_strbuf)++;
        it++;
    }
}

//make a smart copy of the char* into this string

void StringBuffer::smartCopy(char* newString, int length) {
    //(this->_length == length)?:this->_length=length;
    this->_length = length;
    int it = 0;
    while (it < length) {
        *_strbuf++ = *newString++;
        it++;
    }
}
//make a smart copy of this string into the passed string

void StringBuffer::revSmartCopy(char* newString) {
    int it = 0;
    while (it < _length) {
        newString[it] = _strbuf[it];
        it++;
    }
}

void StringBuffer::reserve(int n) {
    if (_length < n) {
        int newlength = n; //max(_length*2,n);
        char* newbuf = new char[newlength];
        //copy contents of the stored string in the new buffer
        this->revSmartCopy(newbuf);

        //return stuff from the new buffer to the stored buffer
        _strbuf = NULL;
        delete[] this->_strbuf;
        this->_strbuf = newbuf;
        this->_length = newlength;
    }
}

//append a character at the end of this String, which has already made a reservation
//Main Assumption: the length has been allocated but not yet utilized and the 
//length counter has not been increased.

void StringBuffer::append(char c) {
    this->_strbuf[this->_length - 1] = c;
}
//get length of the string

int StringBuffer::length() const {
    return this->_length;
}

//get character at index if it is less than length

char StringBuffer::charAt(int index) const {
    if (index < _length) {
        return _strbuf[index];
    } else {
        //throw new IndexOutOfBoundException();

    }
}

class String{
private:
    StringBuffer* _str;
public:
    String();
    ~String();
    String(const String&);
    String(char* ,int);
    void append(char);
    int length() const;
    char charAt(int) const;
};

String::String() {
    this->_str = new StringBuffer();
}
//destructor

String::~String() {

    //decrement the refcount and only if it is =0, delete the buffer.
    if (--this->_str->_refcount < 1) {
        _str = NULL;
        delete[] this->_str;
    }

}

//copy a const String into this string

String::String(const String& newString) {
    this->_str = newString._str;

    //increment the refcount by 1
    ++this->_str->_refcount;
}

//copy a char* into your string

String::String(char* newString, int length) {
    this->_str = new StringBuffer(newString, length);
    //increment the refcount by 1
    this->_str->_refcount = 1;

}

void String::append(char c) {

    //    char* tempbuf = new char[this->_str->length()+1];
    //    this->_str->revSmartCopy(tempbuf);
    if (this->_str->_refcount > 1) {
        //more than 1 reference to this string
        auto_ptr<StringBuffer> newdata(new StringBuffer);
        newdata.get()->reserve(this->_str->length() + 1);
        newdata.get()->smartCopy(this->_str);

        //decrement the reference count to this String
        --this->_str->_refcount;

        //cout<<"length at newdata"<<newdata.get()->length()<<endl;
        //now split the object instances
        this->_str = newdata.release();
    } else {
        this->_str->reserve(this->_str->length() + 1);
    }

    //copy the new character at the end of this string
    this->_str->append(c);

}

//get length of the string

int String::length() const {
    return this->_str->length();
}

//get character at index if it is less than length

char String::charAt(int index) const {
    if (index < this->_str->length()) {
        return this->_str->charAt(index);
    } else {
        //throw new IndexOutOfBoundException();

    }
}

int main(int argc, char** argv) {
    //create a smart string
//    String ss;
    //create a smart string with const char*
    char* hello = "Hello Talha!";
    
    
    
    String ss2(hello,5);
    std::cout<<"ss2 length = "<<ss2.length()<<std::endl;
    cout<<hello<<endl;
    //multiple references
    String ss(ss2);
    cout<<hello<<endl;
    //output statements
    std::cout<<"ss length = "<<ss.length()<<std::endl;
    std::cout<<"new ss charAt 0 = "<<ss.charAt(0)<<std::endl;
    
    //append a character
    ss2.append('w');
    
    //cout<<hello<<endl;
    //hello = "bye";
    
    std::cout<<"new ss length = "<<ss.length()<<std::endl;
    std::cout<<"new ss2 length = "<<ss2.length()<<std::endl;
    
    return 0;
}

