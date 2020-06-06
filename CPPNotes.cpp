/*

Private Constructor
	If class have private constructor, then not allowed to derrived from this class.

CRTP
Curiously Recurring Template Pattern
====================================
https://www.codeproject.com/Articles/603818/Cplusplus-Runtime-Polymorphism-without-Virtual-Fun

overload function
at compile time 
Static polymorphism achieves a similar effect to the use of virtual functions, 
allowing the overloaded functions in the derived classes to be selected at compile time rather than at run time. 
Using CRTP, a "Derived" class inherits a "Base<Derived>" template class where the Base class implements the Derived class’ 
interface functions by typecasting the object and calling its interface member function. 

In order to properly delete instances of derived classes, the Base class is first derived from a general Deletor class 
which defines a virtual destructor. The virtual destructor provides deletion of derived objects through a pointer to the base class. 


class Deletor {
    public:  virtual ~Deletor() {}
};
 
template<typename T> class Base : public Deletor {
    public: 
 
        int  Run() { return static_cast<T*>(this)->DoIt(); }
};
 
class Derived1 : public Base<Derived1> {
    ...
    public:
        int  DoIt() { // the actual implementation for Derived1 
		}
};
 
class Derived2 : public Base<Derived2> {
    ...
    public:
        int  DoIt() { // the actual implementation for Derived2 
		}
};
 
int main() {
    Derived1 Obj1;
    Derived2 Obj2;
 
    Obj1.Run(); // runs the actual DoIt() implementation 
    Obj2.Run(); // runs the actual DoIt() implementation 
};



Function Try Block
==================
http://www.gotw.ca/publications/mill13.htm
https://en.cppreference.com/w/cpp/language/function-try-block

e.g.
class throwingThings
{
	public:
	throwingThings(int i)
	{
		if(i>2)
		{
			throw i;
		}
	}
};
class S
{
	public:
	S(int val) try
	 : tt(val)
	{
	}
	catch(int )
	{
	}
	throwingThings tt;
};

int main()
{
	S s{5};
	return 5;
}

Moral #1: The primary purpose of function-try-blocks is to respond to an exception thrown from the 
member initializer list in a constructor by logging and rethrowing, modifying the exception object and rethrowing, 
throwing a different exception instead, or terminating the program. They are rarely used with destructors or with regular functions.

Function-try-block does not catch the exceptions thrown by the copy/move constructors and the destructors 
of the function parameters passed by value: those exceptions are thrown in context of the caller.

Moral #2: Destructor function try blocks have little or no practical use, because destructors should never emit an exception.[7] Thus there should never be anything for a destructor function try block to detect that couldn't be detected with a normal try block -- and even if there were something to detect because of evil code (i.e., a member subobject whose destructor could throw), the handler would not be very useful for doing anything about it because it couldn't suppress the exception. The best it could do is would be to log something, or otherwise complain.

Moral #3: All other function try blocks have no practical use. A regular function try block can't catch anything that a regular try block within the function couldn't catch just as well.

int f(int n = 2) try {
   ++n; // increments the function parameter
   throw n;
} catch(...) {
   ++n; // n is in scope and still refers to the function parameter
   assert(n == 4);
   return n;
}


Static Lib
Compile and assemple and not link to library.
gcc -c test1.c test2.c
ar rsv testlib.a test1.o test2.o

gcc -o test.out test.c testlib.a
OR
gcc -o test.out test.c -L. -ltestlib
OR
gcc -o driver driver.o -L. -l_mylib
https://www.geeksforgeeks.org/static-vs-dynamic-libraries/


shared library:
gcc -shared -o libmy.so libmy.o

to make available this to all users:
create a module and keep .so there e.g. /usr/locsl/lib/MyLib
cd /etc/ld.so.conf.d/
make a copy of libc.conf - mylib.conf
and mentioned module path there i.e. /usr/locsl/lib/MyLib 

// update cash 
ldconfig
ldconfig -p | grep libmy

To compile prog with shared library:
gcc -L/usr/locsl/lib/tempLib driver.c -o driver -lmy
OR
gcc -shared -o libhello.so -fPIC hello.c/


Important library in C++
<memory>
<assert>
<thread>
<chrono>
<mutex>
<condition_varibale>
<future>
<typeinfo>

//casablanca
<cpprest/http_client>


::Assert::
assert(x==20)
If above condition fails assertion occurs.
Assert should be disabled in run-time.
To disable it-
#define NDEBUG

Internally assert called abort, before it send Expression, file name, Line number to standard error.

exit()
It flushes all unwritten memory/buffer
Remove temp files.
Close all files.
Return exit status to OS.

Abort()
SIGABRT

:: Conversion Function ::
class Y {
  int b;
public:
  operator int();
};
Y::operator int() {
  return b;
}
void f(Y obj) {
  int i = int(obj);
  int j = (int)obj;
  int k = i + obj;
}


char*
=====
char* str = "Akash";   // str[0]='a'; // not allowed // value is const
char s[9] = "Damodhar";  // s = str; // Not Allowed //  pointer is const
	
size_t strlen ( const char * str );

char* str;			// you can get the length of str by using : strlen(str)
				// sizeof() only give size of pointer *str (4 bytes)
				// strlen() not include '\0' char i.e. end char

//char str[10];		// strlen(str) // return 0
			// sizeof(str) // return 10
//char ch[10] = "Akash";  // sizeof(ch) // return 10
			// strlen(ch)  // return 5

//char str[2] = "Akash"; //throws errors - array char too long

//char* str = "Akash";  // sizeof(str) // return 4(size of ptr), if you want to length of string - "Akash", you should use strlen()
			// strlen(str) // return 5(not include \0 char)

char Str[4] = "Aka"; 	// If size is less than the string then error occurs. Internally Str is defined like - char* const Str = "Aka"
Str++;			// Error. Str is a constant
char* ch = Str;	 	// can not increment/decrement the cha array Str, Because Str is a constant pointer
cout<<*(ch++)<<endl;	// output: A // because of post increment operation.


//strstr() - to get sub string
	char * strstr ( const char* str, const char* substr ); 
	if substr present then return char* else return NULL ptr


unsigned char	:	1 byte	0 to 255
signed char	1 byte:	-128 to 127
int	2 or 4 bytes:	-32,768 to 32,767 or -2,147,483,648 to 2,147,483,647
unsigned int:		2 or 4 bytes	0 to 65,535 or 0 to 4,294,967,295

not always. 32-bit compilers also use 4 bytes as the size of an int.

Actually the C language standard says that an int must be at least 16-bits wide. But it doesn't say it has to be exactly n-bits wide. So compiler writers generally go with the word size of the underlying machine - which is 32 bits on most machines today. (Word size is, loosely speaking, the number of bits the processor can physically process at one shot)

Coming to why this is so (why int is the only type without a fixed size), int is the only type where you do not 'interpret' the bits stored in memory. The char type uses ASCII encoding. This encoding was not defined by the C language committee, but since they chose to use it, they had to go with ASCII's 1byte wide characters. So the size of a char was fixed. Storage and encoding of float and double are also defined by IEEE standards, so the C language committee had to fix the size of float to 4 bytes. But when it comes to integral types, there is no encoding standards that specifies the number of bytes to use. So the C language committee chose to leave it undefined to allow compiler writers enough leeway to optimise code according to underlying architectures. It is very truly said that C leans towards the convenience of the compiler writer rather than of the high level user. Accordingly, you see compilers merrily changing the size of int, long and long long according to convenience and underlying architectures, but not messing with ASCII or IEEE.

Exceptions in c/c++
===================
NULL pointer exception - Pointer pointing to the NULL
Dangling pointer       - Pointer deallocated but still pointing the same memory. To avoid it pointer should assign NULL once delete/deallocate.
Array out of bound exception - 
File not found exception - 
Stack/buffer overflow exception
https://www.inf.unibz.it/~calvanese/teaching/06-07-ip/lecture-notes/uni10.pdf
Segmentation fault - pointer try to access the memory which not belongs to it.

Pointers
========
dereferencing operator: * , & , ->

delete and free()
=================
In C++, delete operator should only be used either for the pointers pointing to the memory allocated using new operator or for a NULL pointer
free() should only be used either for the pointers pointing to the memory allocated using malloc() or for a NULL pointer.

Scalar delete:
Delete[] ptr;

int main() 
{
    int** ptr = new int*[3];

	for(int i=0; i<3; i++)
		ptr[i] = new int[3];

	for(int i=0; i<3; i++)
		delete[] ptr[i];

	delete[] ptr;
}

malloc()
	free() 
	delete : destructor gets called, delete can be use with malloc() to delete the memory
new
	free() : free can be used with new to deallocate memory.
	delete : destructor gets called


Storage qualifier in C++
Constant
Mutable
Volatile

IMP keywords
============
explicit, volatile, using, mutable
explicit : to stop internal conversion to object form. Constructor with single parameter(Conversion Constructor)
Conversion function(constructor with single parameter)
explicit
e.g. Top obj = 10;  => it call constructor 
e.g.
explicit A(int a=1){}. // error throws - "can not convert from int to class"

volatile : to tell compiler do not apply optimization on an object. Object value may change.
e.g.
bool flag=false;
if(!flag)
{ // }
In above code, compile assume value of flag may not change and optimize code but
flag value can change in such case should declare flag as a volatile

Why is volatile not considered useful in multithreaded C or C++ programming?
https://stackoverflow.com/questions/2484980/why-is-volatile-not-considered-useful-in-multithreaded-c-or-c-programming


Where/why volatile:

A variable should be declared volatile whenever its value could change unexpectedly. In practice, only three types of variables could change:

1. Memory-mapped peripheral registers

2. Global variables modified by an interrupt service routine
	For example, a global variable can represent a data port
3. Global variables accessed by multiple tasks within a multi-threaded application


using : 	
If base class have the function with same name and different parameters then compiler not allowed to call-
that base class function with derived class object.
Then we need to define base class function in derived with keyword "using"

If super class method is overloaded in Derived class,
then not allowed to call base class function wrt derived class instance.
To resolve this we need to use "using".
using test::fun;

class A
{
    public:
    void foo(string s){};
};

class B : public A
{
    public:
    int foo(int i){};
    using A::foo;
};

class C : public B
{
    public:
    void bar()
    {
        string s;
        foo(s);
    }
};

mutable:
If we need to modify data member in cost member fun or by const object then we need to declare that data member as mutable.
e.g.
class Test
{
    //private:
    public:
        mutable int dm1=20;
        int dm2=50;
    public:
        Test(){cout<<"Test::Constructor"<<endl;}
        void fun() const
        {
            //this->dm2 = 20;  // Not allowed to update dm2 in  const member function
            this->dm1 = 10;
            cout<<dm1<<" "<<dm2<<endl;
        }
        ~Test(){cout<<"Test::Destructor"<<endl;}
};

int main()
{
    const Test obj;
    obj.dm1=19;
    //obj.dm2=29;  // Not allowed to update dm2 as obj is constant
    cout<<obj.dm1<<" "<<obj.dm2<<endl;
    obj.fun();
    return 0;
}
// Case 2
// If object is constant and want to update value of data member, then that data member needs to declare as mutable.
const Base obj;
obj.a =20;
cout<<obj.a<<endl;

----------------------------------------------------------------------------------------------------------

Storage Classes in C
Storage Classes are used to describe about the features of a variable/function.
Features:scope/visibility/life-time

Four storage classes:
Auto
Static
extern
Register: register int i = 10; 

Global and extern
myGlobalVar as you've defined it is a global variable, visible from all the places in your program. There's no need declaring it extern in the same .c file . 
That is useful for other .c files to let the compiler know this variable is going to be used.

Status:
int fun() 
{ 
  static int count = 0; 
  count++; 
  return count; 
} 
   
int main() 
{ 
  printf("%d ", fun()); 
  printf("%d ", fun()); 
  return 0; 
}

Output: 1 2

Smalltalk is a “pure” object-oriented programming language

Difference between C and C++
-----------------------------
C++ is Object Oriented Language?
No. But it support Object oriented programming/features.
Smalltalk is completely Object oriented programming language.
Java is OOP language but it has primitive datatype i.e. "int" not an object of any class.

==========================::program execution process::===============================

.cxx preprocessor-> (.i) compiler ->(.asm) assembler ->(.obj) linker -> .exe/lib

Scopes in C++: Block, function, Class, file

Difference between Structure in C and structure in c++

Access specifiers: private, protected and public
Access specifiers used for Abstraction.

Difference between Structure and Class in C++.	

================================Data Types=====================================
In-build data types(wchar_t, bool, void ) : 
To use bool in C: studbook needs to include. In c++ can use directly.
Derived data types (Array, function, pointer, reference)
Abstract data types / user defined data types(class, structure, union, enum)
===============================================================================

Enum:
enum year{Jan, Feb, Mar, Apr, May, Jun, Jul,  
          Aug, Sep, Oct, Nov, Dec}; 
  
int main() 
{ 
   int i; 
   for (i=Jan; i<=Dec; i++)       
      printf("%d ", i); 
        
   return 0; 
} 
Output:
0 1 2 3 4 5 6 7 8 9 10 11

enum State {Working = 1, Failed = 0, Freezed = 0};


Concrete class	: can create objects.

Data members: Attributes, fields, properties
Member function: Methods, Behaviors, message, operations

Size of Object: All non static DataMemebr + All non static members of base class +
                virtual pointer if virtual function in class(only one VPTR added to object)

Characteristics of objects: state, behavior, identity

C : \n + flush
C++ : endl

Abstract class and Interface
Abstract class:	At least one member function declared as a pure virtual function.
Interface: All member functions declared as pure virtual function. 

Constructor
Types: default constructor, parameterless, parameterized, Copy constructor, Move constructor, Assignment operator function
copy constructor:
Temp(const Temp& obj){} 	// & is must here


Member initializer list /
Constructor initializer list(CIL)	:	array can not initialize with CIL before C++11(from c++11 allowed to initialize array in CIL)
  struct A {
  int foo[3];
  A():foo{1, 2, 3} { }

Whenever class have const or reference type data member it must be initialize with CIL.

If not a single constructor defined by user then only compiler provide default constructor gets called/used.

Constructor Initialiser List:
————————————————————————————
https://www.geeksforgeeks.org/when-do-we-use-initializer-list-in-c/

For initialization of non-static const data members
For initialization of reference members
For Performance reasons
For initialization of member objects which do not have default constructor
For initialization of base class members
	class A { 
    		   int i; 
		   public: 
    			A(int ); 
		}; 
  
		A::A(int arg) 
		{ 
    		  i = arg; 
    		  cout << "A's Constructor called: Value of i: " << i << endl; 
	 	} 
  
	// Class B is derived from A 
	class B: A { 
			public: 
    			B(int ); 
		   }; 
  
		B::B(int x):A(x)
		{ //Initializer list must be used 
    		  cout << "B's Constructor called"; 
		} 
  
		int main() 
		{ 
    		  B obj(10); 
    		  return 0; 
		}


Copy-and-swap idiom
———————————————————
Copy constructor
Assignment operator
Swap function

The standard version of std::swap() will work for most types that are assignable.

void std::swap(T& lhs,T& rhs)
{
    T tmp(lhs);
    lhs = rhs;
    rhs = tmp;
}

Ref: https://stackoverflow.com/questions/1998744/benefits-of-a-swap-function

class dumb_array
{
public:
    // ...

    friend void swap(dumb_array& first, dumb_array& second) // nothrow
    {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // by swapping the members of two objects,
        // the two objects are effectively swapped
        swap(first.mSize, second.mSize);
        swap(first.mArray, second.mArray);
    }

    // ...
};

1. The first is the self-assignment test. This check serves two purposes: it's an easy way to prevent us from running needless code on self-assignment, and it protects us from subtle bugs (such as deleting the array only to try and copy it). But in all other cases it merely serves to slow the program down, and act as noise in the code; self-assignment rarely occurs, so most of the time this check is a waste. It would be better if the operator could work properly without it.

class dumb_array
{
public:
    // ...

    friend void swap(dumb_array& first, dumb_array& second) // nothrow
    {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // by swapping the members of two objects,
        // the two objects are effectively swapped
        swap(first.mSize, second.mSize);
        swap(first.mArray, second.mArray);
    }

    // ...
};

2. The second is that it only provides a basic exception guarantee. If new int[mSize] fails, *this will have been modified. (Namely, the size is wrong and the data is gone!) For a strong exception guarantee, it would need to be something akin to:
dumb_array& operator=(const dumb_array& other)
{
    if (this != &other) // (1)
    {
        // get the new data ready before we replace the old
        std::size_t newSize = other.mSize;
        int* newArray = newSize ? new int[newSize]() : nullptr; // (3)
        std::copy(other.mArray, other.mArray + newSize, newArray); // (3)

        // replace the old data (all are non-throwing)
        delete [] mArray;
        mSize = newSize;
        mArray = newArray;
    }

    return *this;
}
The code has expanded! Which leads us to the third problem: code duplication. Our assignment operator effectively duplicates all the code we've already written elsewhere, and that's a terrible thing.


Solution:
class dumb_array
{
public:
    // ...

    friend void swap(dumb_array& first, dumb_array& second) // nothrow
    {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // by swapping the members of two objects,
        // the two objects are effectively swapped
        swap(first.mSize, second.mSize);
        swap(first.mArray, second.mArray);
    }

    // ...
};
dumb_array& operator=(dumb_array other) // (1)
{
    swap(*this, other); // (2)

    return *this;
}

Move Assignment	operator
------------------------

Move constructor
————————————————
When initialize the object with rvalue then move constructor call.
A move constructor of class T is a non-template constructor whose first parameter is T&&, const T&&, volatile T&&, or const volatile T&&, and either there are no other parameters, or the rest of the parameters all have default values.

Pass parameter as rvalue to a function
e.g.
print(int x);	// call by value
print(int& x);	// call by reference
print(int&& x);	// call by rvalue reference

int a = 10;
print(a);
print(6);

e.g.
simple string class which only holds a pointer to a heap-allocated block of memory:

#include <cstring>
#include <algorithm>

class string
{
    char* data;

public:

    string(const char* p)
    {
        size_t size = strlen(p) + 1;
        data = new char[size];
        memcpy(data, p, size);
    }
Since we chose to manage the memory ourselves, we need to follow the rule of three. 
I am going to defer writing the assignment operator and only implement the destructor and the copy constructor for now:

    ~string()
    {
        delete[] data;
    }

    string(const string& that)
    {
        size_t size = strlen(that.data) + 1;
        data = new char[size];
        memcpy(data, that.data, size);
    }
The copy constructor defines what it means to copy string objects. 
The parameter const string& that binds to all expressions of type string which allows you to make copies in the following examples:

string a(x);                                    // Line 1
string b(x + y);                                // Line 2
string c(some_function_returning_a_string());   // Line 3
Now comes the key insight into move semantics. Note that only in the first line where we copy x is this deep copy really necessary, because we might want to inspect x later and would be very surprised if x had changed somehow. Did you notice how I just said x three times (four times if you include this sentence) and meant the exact same object every time? We call expressions such as x "lvalues".

The arguments in lines 2 and 3 are not lvalues, but rvalues, because the underlying string objects have no names, so the client has no way to inspect them again at a later point in time. rvalues denote temporary objects which are destroyed at the next semicolon (to be more precise: at the end of the full-expression that lexically contains the rvalue). This is important because during the initialization of b and c, we could do whatever we wanted with the source string, and the client couldn't tell a difference!

C++0x introduces a new mechanism called "rvalue reference" which, among other things, allows us to detect rvalue arguments via function overloading. All we have to do is write a constructor with an rvalue reference parameter. Inside that constructor we can do anything we want with the source, as long as we leave it in some valid state:

    string(string&& that)   // string&& is an rvalue reference to a string
    {
        data = that.data;
        that.data = nullptr;
    }
What have we done here? Instead of deeply copying the heap data, we have just copied the pointer and then set the original pointer to null. In effect, we have "stolen" the data that originally belonged to the source string. Again, the key insight is that under no circumstance could the client detect that the source had been modified. Since we don't really do a copy here, we call this constructor a "move constructor". Its job is to move resources from one object to another instead of copying them.

When move constructor gets called:
ABC obj1(10);
ABC obj2 = std::move(obj1);	// call by rvalue reference i.e move constructor called 

Destructor call explicitly:	
When we use placement new i.e. allocate memory for object from existing.
Its bcoz memory not allocated on heap so destructor not calls automatically.
As its not created on heap, not allowed to delete.(delete ptr)Exception throw.

Constructor call explicitly: 
All constructor having more than one parameter are call explicitly.
Relate with explicit keyword.

Information Hiding:	Access specifier
Security :	Mutator(setter) and Inspector(getter) functions.

//----------------------------------------------------------Exception handling------------------------------------------------------------//

Checked: are the exceptions that are checked at compile time. If some code within a method throws a checked exception, 
then the method must either handle the exception or it must specify the exception using throws keyword.

Unchecked: are the exceptions that are not checked at compiled time. In C++, all exceptions are unchecked, 
so it is not forced by the compiler to either handle or specify the exception. It is up to the programmers to be civilized, and specify or catch the exceptions.

When an exception is thrown, all objects created inside the enclosing try block are destructed before the control is transferred to catch block.
E.g.
class Test { 
public: 
   Test() { cout << "Constructor of Test " << endl; } 
  ~Test() { cout << "Destructor of Test "  << endl; } 
}; 
  
int main() { 
  try { 
    Test t1; 
    throw 10; 
  } catch(int i) { 
    cout << "Caught " << i << endl; 
    //delete t1;
  } 
}

Output:
Constructor of Test                                                                                                                   
Destructor of Test                                                                                                                    
Caught 10 


try ......... catch
throw
throw list

each try needs at least one handler catch block just below.

Multiple handlers (i.e., catch expressions) can be chained; each one with a different parameter type. 
Only the handler whose argument type matches the type of the exception specified in the throw statement is executed.

If an ellipsis (...) is used as the parameter of catch, that handler will catch any exception no matter what the type of the exception thrown. 
This can be used as a default handler that catches all exceptions not caught by other handlers:

try {
  // code here
}
catch (int param) { cout << "int exception"; }
catch (char param) { cout << "char exception"; }
catch (...) { cout << "default exception"; }

In this case, the last handler would catch any exception thrown of a type that is neither int nor char.
After an exception has been handled the program, execution resumes after the try-catch block, not after the throw statement!.

Nested try-catch
================
It is also possible to nest try-catch blocks within more external try blocks. 
In these cases, we have the possibility that an internal catch block forwards the exception to its external level. 
This is done with the expression throw; with no arguments.
For example:

try{
  try{
      // code here
  }
  catch (int n) {
      throw;
  }
}
catch (...){
  cout << "Exception occurred";
}


dynamic-exception-speciﬁcations
The use of dynamic-exception-speciﬁcations is deprecated.
throw()
int fun(int n) throw() // for all exception std::unexpected will call
int fun(int n) throw(int) // other than int type of exception std::unexpected will call
noexcept() // will never throw exception


nothrow new		: 
	Test* ptr = nothrow new Test();
By default, one of the versions of operator new is overloaded to accept a parameter of type nothrow_t (like nothrow). 
The value itself is not used, but that version of operator new shall return a null pointer in case of failure instead of throwing an exception.
noexcept : compile time check for excption

e.g.
class ExceptionH
{
	private:
		string errMessage;
		int errCode;
	public:
		
		ExceptionH(string msg, int code):errMessage(msg),code(errCode)
		{}
		string getErrMessage()
		{return this->errMessage;}
		
		int getErrCode()
		{return this->errCode;}
};
class NullPtrException : public ExceptionH
{
	public:
		NullPtrException(string msg="Null pointer Exception", int code=1):ExceptionH(msg,code){}
};

Standard exception:
The C++ Standard library provides a base class specifically designed to declare objects to be thrown as exceptions. 
It is called std::exception and is defined in the <exception> header. This class has a virtual member function called what that returns 
a null-terminated character sequence (of type char *) and that can be overwritten in derived classes to contain some sort of description of the exception.

double myfunction (char param) throw (int);
This declares a function called myfunction, which takes one argument of type char and returns a value of type double. 
If this function throws an exception of some type other than int, the function calls std::unexpected instead of looking for a handler or calling std::terminate.

If this throw specifier is left empty with no type, this means that std::unexpected is called for any exception. 
Functions with no throw specifier (regular functions) never call std::unexpected, but follow the normal path of looking for their exception handler.

int myfunction (int param) throw(); // all exceptions call unexpected
int myfunction (int param);         // normal exception handling 

#include <exception>..............................
using namespace std;

class myexception: public exception
{
  virtual const char* what()
  {
    return "My exception happened";
  }
} myex;

int main () {
  try
  {
    throw myex;
  }
  catch (exception& e)
  {
    cout << e.what() << '\n';
  }
  return 0;
}.................................................


exception				description
bad_alloc		thrown by new on allocation failure
bad_cast		thrown by dynamic_cast when it fails in a dynamic cast
bad_exception		thrown by certain dynamic exception specifiers
bad_typeid		thrown by typeid
bad_function_call	thrown by empty function objects
bad_weak_ptr		thrown by shared_ptr when passed a bad weak_ptr

Also deriving from exception, header <exception> defines two generic exception types that can be inherited by custom exceptions to report errors:

exception			description
logic_error		error related to the internal logic of the program
runtime_error		error detected during runtime

e.g.

#include <exception>
using namespace std;

int main () {
  try
  {
    int* myarray= new int[1000];
  }
  catch (exception& e)
  {
    cout << "Standard exception: " << e.what() << endl;
  }
  return 0;	
}

C++ catch blocks - catch exception by value or reference??
	To handle object from inheritance hierarchy.
	Throw by value, catch by reference
--------------------------------------------------END TRY CATCH----------------------------------------------------------

Modularity

Dynamic Memory allocation
Segment of Memory	:	stack, heap, data(initialized and 7n4), text

Stack
  |
Heap
 |
Data
Uninitialized(static and global var kernel initialized by zero before start execution)
 |
Initialized(static and global var initialized by user)
 |
Text(code segment)

	
Free store

Placement New
    // buffer on stack 
    unsigned char buf[sizeof(int)*2] ; 
  
    // placement new in buf 
    int *pInt = new (buf) int[5]; // allocated int array of 5 int on stack;

------------------------------------------------------------
malloc      		|    		new
------------------------------------------------------------
function		|		operator
			|can be overload
return void*		|return exact object type
			|call constructor
if fails return NULL	|if fails return exception bad_alloc
allocate mem on Heap	|allocate mem on free space
size need to specify	|size calculated by compiler
-------------------------------------------------------------

Function overloading

mangled name
C++ supports function overloading, i.e., there can be more than one functions with same name and differences in parameters. 
How does C++ compiler distinguishes between different functions when it generates object code – it changes names by adding information about arguments. 
This technique of adding additional information to function names is called Name Mangling. 
C++ standard doesn’t specify any particular technique for name mangling, so different compilers may append different information to function names.

Overloading doesn’t work for derived class in C++ programming language. There is no overload resolution between Base and Derived. The compiler looks into the scope of Derived, finds the single function “double f(double)” and calls it.

Constant data Members and member functions, objects and pointers
=================================================================
Static function not able to defined as const.

Mutable keyword:
To allow data member to change in constant member function, we need to declare that data member as mutable.
e.g. mutable int testVar;

Constant data member:
Must to initialize while declaration.
OR
Need to write a constructor/Member initializer list.

Const Member function:
Not allowed to change data member value in const member function.
To allow data member to change in constant member function, we need to declare that data member as mutable.

Const object:
const object can only call const function.

Const object not allowed to call normal functions(non const functions).

Normal object(non const object) can call const function.

const pointer:
e.g. 1.
int x =10;
int* const ptr = &x;

var stored the address of variable x.
So It not allowed to change the value of ptr as it is a const pointer.
Means,
ptr = &y;  // Not allowed

e.g. 2.
int x = 10;
const int* ptr = &x;
OR
int const *ptr = &x;

Now in above case pointer ptr is not const but the pointer ptr pointing to the 
x having value 10 and it is a const.
So it not allowed to change that value of x.
Means,
ptr = &y;  // allowed
but *ptr + 1;  // not allowed.
-------------------------------------------------------------CONST Done-------------------------------------------------------

Reference
It just a another name to the same memory location.
Reference is a constant pointer and thats why Can not reassign value to reference.


e.g.
int z = 21; 
int x = 10; 
int &y = x;  	// y is a another name given to the same memory location.
y++;		// value of y and x both increamented because both pointing to the same mem.
		// Now value on that mem pointing by x and y is changed by 11.
y = z;		// And now value for x,y and z are same and that is 21

Difference between Pointer and Reference
1. Pointer can initialize by NULL, but Reference can not allowed to initialize by NULL.
2. pointer of pointer But reference of reference not allowed.
3. not necessary to initialize the pointer but reference needs to initialize. 
4. Can take the address of pointer but not of reference.


This pointer
-----------
Shallow / Deep copy
When class have pointer type data member then problem occurs.
e.g.
class Temp
{
	int* x;
	int y;
};
Temp obj1;
Temp obj2 = obj1; // Shallow copy because default copy constructor call.
obj2 = obj1;	// Default overloaded assignment operator function call.

Default copy constructor and default overloaded assignment operator function do shallow copy.

So Thumb rule is whenever there is a pointer type data member in class then,
Must be implement the own copy constructor and assignment operator function to implement 
deep copy.

Default Constructor.
Default Destructor.
Default Copy constructor
Default move constructor
Default Assignment operator overloaded function.

Data Structure
Stack: push / pop / top

friend function and friend class
Mutual friend class
Mutual friend function	:	not possible

=====================================Operator Overloading=================================
+ - * /
=
++ -- 
+= -=
< > <= >=
->

// = //
void operator =(const ABC& obj) {}

// Basic Arithmetic : + - * /	//
ABC operator +(const ABC& obj1);

//+=
ABC& operator += (const ABC& obj)
OR
void operator += (const ABC& obj)

Main call:
ABC obj1, obj2, obj3;
obj3 = obj1 + obj2; // obj3 = obj1.operator +(obj2){}

//++, --
void operator ++(){}
OR
void operator ++(int){}
	Prefix:
 	T & operator++() // ++A
        {
            // Do increment of "this" value
            return *this;
        }
	Postfix:
        T& operator++(int) // A++
        {
           // Do increment of "this" value
           return *this;
        }


//	[] 	//
class ABC
{
	string name;
	int age;
	int arr[10];
};

int operator[](int index)
{
	return this->arr[index];
}

e.g. ABC obj;
	int value = obj[2];

//	new	// must return void* only
void* operator new(size_t sz)
	return malloc(sz);

//	delete	//
void operator delete(void* ptr)
	free(ptr);

//	'<<' i.e. cout<<	//
e.g. cout<<obj;	
friend ostream& operator<<(ostream& out, ABC& obj)
{
		out<<obj.name<<obj.age;
		return out;
}

// '>>' i.e. cin>>	//
e.g. cin>>obj;
friend istream& operator>>(istream& in, ABC& obj)
{
	in>>obj.name>>obj.age;
	return in;
}


Why these << and >> operators must be overloaded as global?
In operator overloading, if an operator is overloaded as member, then it must be a member of the object on left side of the operator. For example, consider the statement “ob1 + ob2” (let ob1 and ob2 be objects of two different classes). To make this statement compile, we must overload ‘+’ in class of ‘ob1’ or make ‘+’ a global function.
The operators ‘<<' and '>>' are called like 'cout << ob1' and 'cin >> ob1'. So if we want to make them a member method, then they must be made members of ostream and istream classes, which is not a good option most of the time. Therefore, these operators are overloaded as global functions with two parameters, cout and object of user defined class.

Why need to return ostream reference, even we have a reference of same ostream object as a parameter in operator function?
Ans: its for cascading operations. For example, cout << p1 << endl will be interpreted as (cout << p1) << endl.

while adding const with object , there must be a 
1. constructor with one parameter and 
2. implement +(or any other) operator overload function and define it as a friend in that class.
e.g.
main call:
Temp obj1;
Temp obj2 = 1 + obj1;

friend function declaration will be:
Temp& operator+(const Temp& obj1, const Temp obj2);  // const is must  

e.g.
class A
{
	int _a;
public:
	A(int a=1) 
	{ 
		cout << "\nConstructor A(int a)\n";
		_a = a; 
	}
	A operator+(A obj1)
	{
		cout << "\n A: operator +";
		A temp;
		temp._a = this->_a + obj1._a;
		return temp;
	}
	int GetA()
	{
		return this->_a;
	}
	friend A operator +(const A& obj1, const A& obj2);
};
A operator +(const A& obj1, const A& obj2)
{
	cout << "\nFriend operator +";
	A temp;
	temp._a = obj1._a + obj2._a;
	return temp;
}

int main()
{
A obj(10);
A obj1 = 1 + obj + obj;
cout<<obj1.GetA(); // output: 21
}

Output:
--------------------------
Constructor A(int a)  // obj(10)
Constructor A(int a)  // 1 + obj

Friend Operator + called
Constructor A(int a)	// obj = obj+obj

A: Operator + called
Constructor A(int a)	//obj1 = (1 + obj + obj)
21
--------------------------

operator cant overload:- 	?: :: sizeof .*(pointer to member selection), ., typeid

------------------------------------------------- :: Static :: -----------------------------------------------------
Static data member:
	Refer by class name and wrt object
	can we initialize static member in constructor?
	ans: we can not initialize static member into constructor, because we must need to initialize static member while declaring it or before start main function.(i.e. in .cpp file)
		Yes we can assign value to static member in constructor.  But not initialize there.
	
Static member function:
	Refer by class name and wrt object
	Only static data member can use inside static member function.
e.g. Object count.
A static member function cannot be declared with the keywords virtual , const , volatile , or const volatile.

We can declare static member as constant. But if we declared static member as const, we need to initialize the member while declaring it.
Then after not allowed to update the value of static const data member.

class ABC
{
  static const int a=900;
  public:
    int getA()
    {
        return a;
    }
};

int main()
{
    ABC obj;
    cout<<obj.getA();
    return 0;
}

Next, We can observed here that we can use static const data member in member function.
If static member declare as public, then we can access it with object: cout<<obj.a;


//	OOPs	//
=====================================================================================
Minor pillor: Polymorphism, Persistens, Concurancy
Major pillor: Abstraction, Encapsulation, Modularity, Hierarchy(is-a has-a creates-a)

Abstraction: 
Hiding complexity.
Access specifiers are the main pillar of implementing abstraction in C++. We can use access specifiers to enforce restrictions on class members.
i.e. private/public/protected
 
Relation:  https://www.visual-paradigm.com/guide/uml-unified-modeling-language/uml-aggregation-vs-composition/
	1. Associations
	2. Generalization - (creating generalized class from more specific classes having common features)Inheritance	
	3. Specialization - (creating new specialize class from generic class with some additional features)opposite inheritance
	3. Aggregation	  -  child may exist without parent   (classRoom-student, student can exist without classRoom)	
	4. Composition	  -  child can not exist without parent (House-Room, Room can not exist without House)
	5. Realization
	6. Dependency

//	Polymorphism	//
use derived class via base class pointer
Polymorphic class:	class having virtual function
Polymorphism Types:
subType		(runtime polymorphism)
Parametric	(compile time polymorphism)
ad-hoc		(overloading)
coercion	(implicit or explicit) casting

Why need Polymorphism:
"Imagine a base class Shape. It exposes a GetArea method. Imagine a Square class and a Rectangle class, and a Circle class. 
Instead of creating separate GetSquareArea, GetRectangleArea and GetCircleArea methods, 
you get to implement just one method in each of the derived classes. You don't have to know which exact subclass of Shape you use, 
you just call GetArea and you get your result, independent of which concrete type is it."

Diamond Problem / Virtual Base class
In order to keep track of the single instance of the storable object, 
the compiler will provide a virtual function table (vtable) for classes transmitter and receiver. 
When a radio object is constructed, it creates one storable instance, 
a transmitter instance and a receiver instance. The transmitter and receiver classes have a virtual pointer 
in their vtables that stores the offset to the storable class. 
When the transmitter class or the receiver class goes to access any fields of the storable, 
it uses the virtual pointer in its vtable to find the storable object and find the field in it.

virtual
pure virtual function
function overriding
Virtual pointer : for each class only one Virtual pointer
Virtual Table	: for each class only one Virtual table

How to resolve virtual/override function calling at run time,
e.g.
Base* ptr = new Der();
ptr->area();	// If function area() in base class not defined as virtual then area() from base class call by default.

Thats why,
1. Whenever there is a override function in derived class, define function in base class as virtual.
e.g. virtual void area();
2. Now whenever there is a function defined as virtual 'compiler' creates a virtual table for each class.
3. And if the base class have virtual function and Derived class dont have any virtual function, still compiler create one Virtual table for base class and one for derived class.
	Because if the base class function defined virtual and derived class have overridden function then automatically that function in derived class 
	becomes a virtual function.
4. If derived class not override base class virtual function, still virtual table created for derived class and add one entry for each base class virtual function in
	derived class virtual table.
5. If there is a virtual destructor in base class, then entry of the destructor all be added in virtual table of base class. And add entry of destructor of every class in their own class's
	virtual table. 
6. When base pointer/reference call a virtual function, then in constructor check if it is a virtual function then it adds one 
	VPTR(pointer which points to that class virtual table) to the object. VPTR is for each object. Assign in constructor.
7. And using that VPTR compiler able to know which virtual function from which class needs to be called.
8. Virtual Function Table:
	One virtual table for each class.
	Virtual Table contains the address of all virtual functions in class.
	Its created at compile time.

Example:
#include<iostream.h>

class Base  
 {  
 public:  
    virtual void function1() {cout<<"Base :: function1()\n";};  
    virtual void function2() {cout<<"Base :: function2()\n";};  
    virtual ~Base(){};
};  
   
class D1: public Base  
{  
public:  
   ~D1(){};
   virtual void function1() { cout<<"D1 :: function1()\n";};
};  
  
class D2: public Base  
{  
public:  
   ~D2(){};
   virtual void function2() { cout<< "D2 :: function2\n";};  
};  

int main()
{
  D1 *d = new D1;;
  Base *b = d; 

  b->function1();
  b->function2();

  delete (b);
  
  return (0);
}

output:
D1 :: function1()
Base :: function2()

Base - Virtual Table
---------------------
fun1
fun2
~Base

D1 - Virtual Table
-------------------
fun1
Base_fun2
~D1

D2 - Virtual Table
------------------
fun2
Base_fun1
~D2


------------------------------------------------ Casting: Down casting and Up casting ------------------------------------------------

Type casting
-------------
Traditional explicit type-casting allows to convert any pointer into any other pointer type, independently of the types they point to. 
The subsequent call to member result will produce either a run-time error or a unexpected result.

Ref : http://www.geeksforgeeks.org/casting-operators-in-c-set-1-const_cast/
C++ supports following 4 types of casting operators:

1. const_cast
2. static_cast
3. dynamic_cast RTTI
4. reinterpret_cast

1. const_cast

	C-style casts are prone to errors because they are such a blunt instrument. 
	With C++ casts, you indicate your intention and the compiler can check to see if your intention is legal.


	// Ex1
	const char* str1 = "string";
	//char* str2 = (char*)str1;        // C style
	char* str2 =  const_cast<char*>(str1);
	cout<<str2<<endl;  // string

	// Ex2
	const char* str = "string";
	fun(const_cast<char*>(str));
	
	 // Ex3
	int a = 10;
	const int* ptr = &a;
	char* str3 = (char*)ptr;  // No compile time error
	cout<<*str3<<endl;			// Nothing will print
	//char* str4 = const_cast<char*>(ptr);  // Compile Error::Not allowed to cast int pointer to char pointer

	// Ex4
	// const volatile int* to int*
	int no = 10;
	const volatile int* ptrNo = &no;
	// int* newPtr = ptrNo;  // Compile time Error:: Not allowed
	int* newPtr = const_cast<int*>(ptrNo);


typeid and type_info
======================
#include <typeinfo>
	const std::type_info& ti1 = typeid(a1);
	cout << "\n "<<ti1.name();
	cout << "\n " << ti1.hash_code();


static_cast
=============
static_cast can perform conversions between pointers to related classes, not only upcasts (from pointer-to-derived to pointer-to-base), but also downcasts (from pointer-to-base to pointer-to-derived). No checks are performed during runtime to guarantee that the object being converted is in fact a full object of the destination type. Therefore, it is up to the programmer to ensure that the conversion is safe.

For class pointer: Upcast and downcast
For class object : only Upcast

class Base
{
private:
	int a;
public:
	Base()
	{
		cout<<"Base::Constructor"<<endl;
	}
	~Base()
	{
		cout<<"Base::Destructor"<<endl;
	}
	void print()
	{
		cout<<"Base::print"<<endl;
	}
};
class Der : public Base
{
private:
	int b;
public:
	int x;
	Der()
	{
		cout<<"Der::Constructor"<<endl;
	}
	~Der()
	{
		cout<<"Der::Destructor"<<endl;	
	}
	void print()
	{
		cout<<"Der::Print"<<endl;
	}
};

// implicit static casting allowed
float f = 3.5; 
int a = f; // this is how you do in C 
//int b = static_cast<int>(f);  // Allowed
int b = f;
cout << b;

// C style allowed but C++ casting Not allowed
int a = 10;
int* ptrA = &a;
float* fptr = (float*)ptrA;
//float* fptr = static_cast<float*>(ptrA);


// Up casting Always allowed
Der derObj;
//Base baseObj = derObj;
Base baseObj = static_cast<Base>(derObj);

// Up casting, When private inheritance
Der* newptr = new Der();
Base* newptr1 = (Base*)newptr;  // Allowed
//Base* newptr1 = static_cast<Base*>(newptr);  // Not Allowed


// Down Casting with object always not allowed
Base baseObj1;
//Der derObj1 = (Der)baseObj1; // Not allowed
//Der derObj1 = static_cast<Der>(baseObj1);  // Not allowed

// Down Casting with pointer allowed with explicit casting, but its not safe.
Base basePtr1;
//Der* derPtr1 = (Der*)&basePtr1; // allowed
Der* derPtr1 = static_cast<Der*>(&basePtr1);  // Allowed
derPtr1->print();   // Derived class print function gets called
cout<<derPtr1->x;  // Not safe while accessing derived class specific date


Dynamic_cast(take pointer/reference only)
========================================
dynamic_cast is useful when you don't know what the dynamic type of the object is. \
It returns a null pointer if the object referred to doesn't contain the type casted to as a base class 
(when you cast to a reference, a bad_cast exception is thrown in that case).

if(Der_1 *j = dynamic_cast<Der_1*>(&stm))
{
  ...
} 
else if (Der_2 *e = dynamic_cast<Der_2*>(&stm)) 
{
  ...
}

You cannot use dynamic_cast if you downcast (cast to a derived class).
And the argument type is not polymorphic. 

An "up-cast" (cast to the base class) is always valid with both static_cast and dynamic_cast, 
and also without any cast, as an "up-cast" is an implicit conversion.


Down->top
Base* ptr = new Der(); // dynamic_cast should use here
e.g.
Base* ptr = dynamic<Base*>(new Der());

Top->Down
Der* ptr = new Base(); // Error

Reinterpret
============---------------------------------------------------------------
reinterpret_cast converts any pointer type to any other pointer type, even of unrelated classes. 
The operation result is a simple binary copy of the value from one pointer to the other. 
All pointer conversions are allowed: neither the content pointed nor the pointer type itself is checked

----------------------Object Slicing----------------------
In C++ In C++, a derived class object can be assigned to a base class object, but the other way is not possible. 
Object slicing happens when a derived class object is assigned to a base class object, additional attributes of a derived class object are sliced off to form the base class object.


---------------------- :: Volatile :: --------------------

int some_int = 100;
while(some_int == 100)
{
   //your code
}

As the value of some_int never gone change till the while condition,
Compiler may do some optimization here and while loop may change to 
	> while(true) <
But sometime optimization may undesirable.

To avoid such optimization from compiler we can use "volatile"
e.g.
volatile int some_int = 100;	//"Don’t change code when I am present"
-----------------------------------------------------------------------

Early Binding and Late binding
Algo:
IF---> fun is not a member of caller type
			::ERROR
ELSE
	IF---> caller is Object type(not a pointer)
			::Early Binding
	ELSE
		IF---> fun is not a VIRTUAL type
			::Early Binding
		ELSE
			::Late Binding
=============================================

Virtual function with default values

If Base class have a virtual function with default argument value
sub class override method must also have argument with default value(value may change)
But while function call default value is set as per the type of object not the actual address of object.


virtual Constructor : not allowed
virtual Destructor  : when we do up-casting at that time on delete object pointer only base class Destructor calls.
So to call derived class destructor we need to declare base class Destructor as a virtual.

*****Operator function*****
*****Inline function*****
12w
*****Namespace*****
// Variable created inside namespace 
namespace first 
{ 
    int val = 500; 
} 

Inheritance: 
Single, Multilevel, Multiple, Hierarchical, Hybrid
Diamond Problem / Diagonal problem (Virtual Inheritance)
***Interface inheritance***
***Implementation inheritance***

Abstract class
	At least one member function must be pure virtual function
pure Abstract class / Interface
	All member function must be pure virtual function

:: RAII ::
==========
Resource Aquisition is Initialization

RAII is the design paradigm to ensure that variables handle all needed initialization in their constructors and all needed cleanup 
in their destructors. This reduces all initialization and cleanup to a single step.

C++ does not require RAII, but it is increasingly accepted that using RAII methods will produce more robust code.

The reason that RAII is useful in C++ is that C++ intrinsically manages the creation and destruction of variables as they enter 
and leave scope, whether through normal code flow or through stack unwinding triggered by an exception. That's a freebie in C++.

By tying all initialization and cleanup to these mechanisms, you are ensured that C++ will take care of this work for you as well.

Talking about RAII in C++ usually leads to the discussion of smart pointers, because pointers are particularly fragile when 
it comes to cleanup. When managing heap-allocated memory acquired from malloc or new, 
it is usually the responsibility of the programmer to free or delete that memory before the pointer is destroyed. 
Smart pointers will use the RAII philosophy to ensure that heap allocated objects are destroyed any time the pointer variable is destroyed.


Smart pointer
=============
#include<memory> 

In case on non-smart pointer used and allocate memory on heap,
when exception occurs then need to delete object explicitly in catch block.

In case of smart pointer no need to delete object explicitly in catch block.
While stack unwinding, destructor of smart pointer calls automatically. 


Auto_ptr - Its deprecated from C++ 11 and new uniquePtr introduced
unique_ptr
shared_ptr

Auto_ptr
	Auto deleted when goes out of scope
	It allows to change the ownership.
	It takes ownership of the pointer in a way that no two pointers should contain the same object. 
	Assignment transfers ownership and resets the rvalue auto pointer to a null pointer. 
	Thus, they can’t be used within STL containers due to the aforementioned inability to be copied.
	
	e.g.
	auto_ptr<int> p1(new int(10));
    	auto_ptr<int> p2;
    	p2 = p1;		// calls destructor
    	cout<<p1.get()<<endl;
    	cout<<p2.get()<<endl;
    	cout<<*p1<<endl;        // Segmentation fault occurs

	Output:
		0                                                                                                                                       
		0x199fc40                                                                                                                               
		Segmentation fault (core dumped)
	Since objects within an STL container must be copy-constructible and assignable, a compile time error is provided if an auto_ptr is used within a container. 
	Algorithms, such as those involved in sorting STL containers, often copy objects while carrying out their tasks.

Unique_ptr
==========
	Auto deleted when goes out of scope and also not allowed to make copy of this.
	get(): get the memory address of pointer
	move():
		unique_ptr<A> p1 (new A); 
		unique_ptr<A> p2 = move(p1);

		unique_ptr<int> ptr1(new int(10));
    		unique_ptr<int> ptr2;
    		ptr2 = move(ptr1);
    		cout<<*ptr2<<endl;
    		cout<<*ptr1;		// segmentation fault
Use:
	unique_ptr<Top> ptr(new Top());
    	ptr->Fun1();

With STL::container
	unique_ptr<Base> uptr1(new Base());
	vector<unique_ptr<Base>> v;
	v.push_back(std::move(uptr1));
	uptr1->print();  // once move to other, uptr1 not allowed to use and get exception.
	
SharedPtr
=========
	Can make copy of this type of pointer.
	It maintains a reference count internally and only deletes the resource when the reference count goes to zero.
	copy:
	shared_ptr<A> p1 (new A); 
    shared_ptr<A> p2 (p1); 
	get(): get the memory address of pointer 
	use_count(): get the count of total number string this pointer

make_shared()
This function uses ::new to allocate storage for the object. 
A similar function, allocate_shared, accepts an allocator as argument and uses it to allocate the storage.
allocate_shared()
	Same as above but it use alloc() to allocate memory.
	
shared_ptr<int> sptr = make_shared<int>(10);


weak_ptr
========
	shared_ptr<Base> sptr1(new Base("sptr1"));
	shared_ptr<Base> sptr2 = make_shared<Base>(obj);

	weak_ptr<Driver> wptr1 = sptr1;
	if(sptr1 = wptr1.lock())
		sptr1->print();
	else
		cout<<"mptr1 is expired"<<endl;



***Avoiding cyclic references when using shared pointers***
In many situations , when a class contains a shared_ptr reference , you can get into cyclical references. 

So our initial design introduced a self referential shared_ptr inside the Driver class:

class Driver
{
public:
	string name;
	weak_ptr<Driver> partner;  // If shared_ptr used instead of weak_ptr then cyclic dependancy 
							  // created and therefore destructor never gets called 

public:
	Driver(string _name)
	{
		cout<<_name<<": Constructor"<<endl;	
		name = _name;
	}
	Driver()
	{
		cout<<"Constructor"<<endl;	
	}
	void print()
	{
		shared_ptr<Driver> sh = partner.lock();
		cout<<name<<" partenr : "<<sh->name<<endl;
	}
	~Driver()
	{
		cout<<this->name<<": Destructor"<<endl;
	}
};

int main()
{
	shared_ptr<Driver> obj1 = make_shared<Driver>("A");
	shared_ptr<Driver> obj2 = make_shared<Driver>("B");
	//OR
	//shared_ptr<Driver> obj1(new Driver("A"));
	//shared_ptr<Driver> obj2(new Driver("B"));
 
	obj1->partner = obj2;
	obj2->partner = obj1;

	obj1->print();
	obj2->print();
}


	
//	Auto_ptr	//
#################

class Person
{
	Private:
		string _name;
		int _age;
	public:
		Person(){}
Sort		Person(string name, int age):_name(name),_age(age){}
		void Display(){};
};

class SP
{
	Person* _ptr;
	
	public:
	SP(Person* ptr):_ptr(ptr){}
		~SP()
		{delete _ptr;}
	Person* operator->()
	{return _ptr;}
	Person& operator*()
	{return *_ptr;}
	
	// copy constructor
	Person(const Person& ptr)	// because std auto_ptr implement this
	{
		Person* temp = &ptr;
		delete &ptr;
	}
	// assignment operator overload
	Person* operator=(const Person& ptr)	// because std auto_ptr implement this
	{
		Person* temp = &ptr;
		delete ptr;
		return temp;
	}
};
void main()
{
	SP p(new Person("akash"),26);
	p->Display();
}

//	Using Template	//
template<typename T> class TSP ;;;;;;;;;;;;;classname
{
	T* _ptr;
	public:
		TSP(T* ptr):_ptr(ptr){}
		~TSP()
		{delete _ptr;}
		T* operator->()
		{return _ptr;}
		T& operator*()
		{return *_ptr;}
};
void main()
{
	TSP<Person> obj(new Person("akash",26));
	obj->Display();
}

Problem with auto_ptr
---------------------
void main()
{
    SP<PERSON> p(new Person("Scott", 25));
    p->Display();
    {
        SP<PERSON> q = p;
        q->Display();
        // Destructor of Q will be called here..
    }
    p->Display();
}
p and q are referring to the same Person class pointer. Now when q goes out of scope, the destructor of q will be called which deletes the Person class pointer. 
Now we cannot call p->Display(); since p will be left with a dangling pointer and this call will fail.

Ref: https://www.codeproject.com/Articles/15351/%2FArticles%2F15351%2FImplementing-a-simple-smart-pointer-in-c


// STL  //
======================================Standard Template Library======================================
Basics
------
Iterator:
Forward
	vector<int>::iterator it;
Reverse
	vector<int>::reverse_iterator it;
	Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning). 
	Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container. 
	rbegin points to the element right before the one that would be pointed to by member end.

Container class templates
Sequence containers:
Array
Vector
Deque
forward_list
list

Container adaptors:
stack
queue
priority_queue

Associative containers:
set
multiset
map
multimap

Unordered associative containers:	
unordered_set
unordered_multiset
unordered_map             --------- Its equivalent to the Hash Table
unordered_multimap

auto_ptr can not use with str containers.

//  1. vector  //
Underline Implementation : by 1-d Array
elements at Continuous memory 
[] can use to access

::Time Complexity::
Accessing is fast : O(1)
Insertion deletion is slow exp : (n)
Push_back - O(1) but in case previous allocated memory is full and need to allocate new memory for all elements and move them to new place then it takes O(n)
pop_back - O(1)


vector<int>::iterator
function: begin(),end(),push_back(),pop_back(),front(), size()
insert(initial pointer,position,value)

Initialise vector:

vector<int> vect{ 10, 20, 30 }; 		//like Array
Vector<int> v(5);						// 5 element added with default value zero
Vector<int> v(5, 7);						// 5 elements added with same value 7
Vector<int> v(v1);						// initialized with another vector
Vector<int> v(arr->start, arr->end);		// initialized with Array
Vector<int> v(set.begin(), set.end());		//initialized with std::s ::
Insert  (return: An iterator that points to the first of the newly inserted elements or position which send in insert function)

::Erase::  returns the iterator points to next element
iterator erase (const_iterator position);
iterator erase (const_iterator first, const_iterator last);

Erase: (return: returns the iterator points to next element)
    Vector<int> v = {11,2};
    vector<int>::iterator t = v.erase(it);       // it returns the iterator points to next element
    cout<<*t<<endl;
    //v.erase(it);      //It throws null pointer exception if it is null

erase(position_of_nth_element)	
	e.g. erase(v.begin()+5)	: 5th element will delete
erase(starting_position,number_of_element)	
	e.g. erase(v.begin(), v.begin()+3)	:	3 elements from begining will delete

vector and Iterator Invalidation.

::Find::

std::Find(return: An iterator to the first element in the range that compares equal to val or end of iterator)
  int myints[] = { 10, 20, 30, 40 };
  int * p;
  p = std::find (myints, myints+4, 30);

// using std::find with vector and iterator:
  std::vector<int> myvector (myints,myints+4);
  std::vector<int>::iterator it;

  it = find (myvector.begin(), myvector.end(), 30);
  if (it != myvector.end())
    std::cout << "Element found in myvector: " << *it << '\n';
  else
    std::cout << "Element not found in myvector\n";

If maximum number of item is known, then use reserve(MAX) function.
e.g. v.reserve(20).

If maximum number item is unknown, then receive as much as you can and once all data inserted,
trim off the rest.
e.g. v.shrink_to_fit();

reserve()/capacity()/shrink_to_fit()
    vector<int> v;
    v.reserve(20);
    v.push_back(1);
    v.push_back(1);
    v.push_back(1);
    v.push_back(1);
    cout<<sizeof(v)<<endl;	//24 - its a constant, It takes the size off class.
    cout<<v.size()<<endl;		//4
    cout<<v.capacity()<<endl;	//20
    v.shrink_to_fit();
    cout<<v.capacity();	//4

Initially when vector is empty then its capacity is zero.

::::Importance of Constructors while using User Defined Objects with std::vector::::
For User Defined classes if Copy Constructor and Assignment Operator are public then only one can insert it’s object in std::vector.
This is because of two reasons,
* All STL contains always stores the copy of inserted objects not the actual one. So, whenever we insert any element or object in    container then it’s copy constructor is called to create a copy and then this copy is inserted in the container.
* While insertion in std::vector it might be possible that storage relocation takes place internally due to insufficient space. In such cases assignment operator will be called on objects inside the container to copy them from one location to another.

https://thispointer.com//importance-of-constructors-while-using-user-defined-objects-with-stdvector/

// queue // 
1-d array
[] not allowed
No iterator
operations: push/pop/front

//	2. Deque	//
Double ended queues are sequence containers with the feature of expansion and contraction on both the ends. They are similar to vectors, 
but are more efficient in case of insertion and deletion of elements at the end, and also the beginning. Unlike vectors, contiguous storage allocation may not be guaranteed.

The outer vector contains pointers to the inner vectors. When its capacity is changed via reallocation, rather than allocating all of the empty space to the end as std::vector does, 
it splits the empty space to equal parts at the beginning and the end of the vector. This allows push_front and push_back on this vector to both occur in amortized O(1) time.

No reallocation.
Deque has no reserve() and capacity().
Slightly slower than vector:
	complex data structure.



Implemented by vector of vector(but not std::vector)
elements not at Continuous memory 
[] can use to access
deque<int>::iterator
function:	begin(), end(), push_back(), pop_back(), push_front(), pop_front(),front()
insert(iterator position, value);
erase(deque.begin(),nth ele pointer);
Insertion/Deletion is slow: O(n)
Accessing is fast : O(1)

//	3. List	//
Implemented by standard doubly LinkList
list<int>::iterator
function: begin(), end(), push_back(), pop_back(), push_front(), pop_front()
insert(iterator position, value);
erase(list.begin(), nth ele pointer)	//use iterator
advance (it2,6);

  std::list<int> mylist;
  std::list<int>::iterator it1,it2;

  // set some values:
  for (int i=1; i<10; ++i) mylist.push_back(i*10);

                              // 10 20 30 40 50 60 70 80 90
  it1 = it2 = mylist.begin(); // ^^
  advance (it2,6);            // ^                 ^
  ++it1;                      //    ^              ^

  it1 = mylist.erase (it1);   // 10 30 40 50 60 70 80 90
                              //    ^           ^

  it2 = mylist.erase (it2);   // 10 30 40 50 60 80 90
                              //    ^           ^

  ++it1;                      //       ^        ^
  --it2;                      //       ^     ^

  mylist.erase (it1,it2);     // 10 30 60 80 90


Insertion/Deletion is not fast than vector : O(n)
But extra ooverload of shifting elements are not needed in list.
Accessing is slow : O(n)

//	4. Set	// All operations - O(log n)

Ordered Set and Map are balanced binary search tree (Red-Black Tree)  Thus, you use them when you want insertion ,searching, deletion in O(log n). They don't allow duplicates.

Unordered Set and Map are an implementation of Hash Tables. So, you use them when on average you want insertion, search, deletion in O(1). Though, worst case will O(n).

Red-Black tree
Implemented as Balance/AVL Tree/ Binary search tree
[] not allowed
set<int>::iterator :  use to traverse set

Elements are ascending order
The default comparator is less, so the set will be ordered ascending. 
To change this you can specify another existing or custom comparator as a template argument.
e.g. set<int, std::greater<int>>set;

No duplicates allowed
::insert::
	insert(list.begin(), value);
	// using insert() to insert single element 
	// inserting 20 
    	ptr = st.insert(20); 

	// inserting array elements in set 
    	// 24 is not inserted again 
    	int arr[3] = { 25, 24, 26 }; 
    	st.insert(arr, arr+3); 

If insert a duplicate value to set, what is return value?
std::pair<iterator,bool> 
So check for 
auto a = s.insert(10);
if(a.second)
{}

Below operations not return any value
void insert( InputIt first, InputIt last );	
void insert( std::initializer_list<value_type> ilist );

::Find:: O(logN)
What it means for set to be an Associative Container is that you can look up a value, by writing
Set<int>::iterator it = S.find("foo");.
If the lookup is successful then find returns an iterator that points to the appropriate element in the set. If there
is no such element then find returns the iterator S.end(), which doesn't point to anything.

::erase::
erase(list.begin(), nth ele pointer)	//use iterator
e.g. 
erase(value);
erase(it);
erase(it,set.end());

return iterator of last removed value.

// remove all elements up to 30 in set2 
    set2.erase(set2.begin(), set2.find(30)); 

// remove element with value 50 in set2 
    int num; 
    num = set2.erase (50); 


::empty::
empty() – Returns whether the set is empty

The value of the element cannot be modified once it is added to the set, though it is possible to remove and add the modified value of that element.

// assigning the elements from set1 to set2 
    set <int> set2(set1.begin(), set1.end()); 


operator '<' must be overloaded if Set is using with class objects.
i.e. bool operator <(const TestClass& obj)const

Use:
1. Print sorted distinct element

A practical problem based on unordered_set – given a set of integer number, find duplicate among them

Multiset: allow duplicate
unordered_set: elements in unorder state  (unordered_set.h needs to include)

(Lowest speed)--To access individual element--(Fastest)
Set < Multiset < Unordered_Multiset < Unordered_Set


//	5. Map	// all operation - O(log n)
Implemented by - BST (Red black tree : less complexity in order to insert,delete and searching)
map<int,int>::iterator
Elements are ascending orderd: and  index is fixed
No duplicates allowed
insert(pair<init,int>(1,100));
insert(make_pair(1,100));

    map<int, int> m; 
  
    m[1] = 2; // Insertion by indexing 
  
    // Direct pair insertion 
    m.insert({ 4, 5 }); 
  
    // Insertion of pair by make_pair 
    m.insert(make_pair(8, 5));  

erase(index);
extract(key)
Value can modify in map.

Multimap: allow duplicate
unordered_map: elements in unorder state (unordered_map.h needs to include)

Both set and map are implemented by same data structure i.e. Balance tree
for search use binary search so complaexity is same for both. i.e. O(log n) 
for operation search/insert/delete : O(log n)

hash_map
--------
implemented by array of link list so complexity is best: O(1) and worst: O(n)

Underline data structure:
map - red-black trees(Map internally uses self-balancing BST)
unordered_map - hash tables. 
Multimap - self-balancing BST
Unorder-Multimap - same as that of unordered_map i.e. Hash Table 
but for duplicate keys another count value is maintained with each key- value pair

The standard doesn't mandate much so if you can come up with other data structures that fit both functional and complexity 
requirements of the C++ standard then all is fine.
For example the implementation shipped with VisualStudio is based on a red-black tree.

  	 	
Stroustrup, in The C++ Programming Language (4th Edition) states "It is implemented as a balanced binary tree"


Set vs Map
----------
For example consider in the problem of printing sorted distinct elements, we use set as there is value needed for a key. 
While if we change the problem to print frequencies of distinct sorted elements, we use map. We need map to store array values as key and frequencies as value.

 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
Node Handle
------------
std::map< int, std::string > all_numbers
    { {0,"zero"}, {1,"one"}, {2,"two"}, {3,"three"}, {4,"four"}, {5,"five"}, {6,"six"}, {7,"seven"} } ;
    std::cout << "all numbers (map, before move): " ;
    for( const auto& pair : all_numbers ) std::cout << "{ " << pair.first << ", " << pair.second << "} " ;
    std::cout << '\n' ;

    std::multimap< int, std::string > odd_numbers { {1,"one"}, {5,"five"}, {9,"nine"} } ;

    // move odd numbered items from map all_numbers into multimap odd_numbers
    // (we can move nodes from a map to a multimap if the value_type and allocator_type of both are identical;
    // the node handles are compatible.). inserting an empty node handle does nothing.
    // note that node handles can't be copied; they must be moved 
    for( int key = 1 ; key < 1000 ; key += 2 ) odd_numbers.insert( all_numbers.extract(key) ) ;

    std::cout << "even numbers (map, sfter move): " ;
    for( const auto& pair : all_numbers ) std::cout << "{ " << pair.first << ", " << pair.second << "} " ;
    std::cout << '\n' ;

    std::cout << "        odd numbers (multimap): " ;
    for( const auto& pair : odd_numbers ) std::cout << "{ " << pair.first << ", " << pair.second << "} " ;
    std::cout << '\n' ;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


===========================================================================================

extern "C"
----------

How to handle C symbols when linking from C++?
In C, names may not be mangled as C doesn’t support function overloading. So how to make sure that name of a symbol is not changed when we link a C code in C++. 
For example, see the following C++ program that uses printf() function of C.

// Save file as .cpp and use C++ compiler to compile it 
int printf(const char *format,...); 
  
int main() 
{ 
    printf("GeeksforGeeks"); 
    return 0; 
} 

Output:
undefined reference to `printf(char const*, ...)'
        ld returned 1 exit status


// Save file as .cpp and use C++ compiler to compile it 
Extern "C"
{
    int printf(const char *format,...); 
} 
int main() 
{ 
    printf("GeeksforGeeks"); 
    return 0; 
} 




atoi,	stoi,	stol,	stod

Local class	:	class defined inside function
virtual class 	:	inner class defined as virtual
scaler delete	:	delete[] ptr;

Nested class
-------------
class A
{
	int x;
public:
	class Aa
	{
		int y;
	public:
		Aa() { cout << "A::Aa::constructor"; }
		// we can access members of outer class-A into inner class e.g. x can be accessible here
	};

public:
	void Display()
	{
		cout << "Class: A ";
		cout<<y;	// not allowed because y defined in private section of inner class
	}
};

int main()
{
	A obj;
	A::Aa obj2; // valid

	_getch();
	return 1;
}


//	Function pointer	//
============================
typedef void (*fun) (int);
void function(int a)
{}

calling:
fun f = &function;
f(10);
============================

===============
Design Pattern
===============
1.	Creational Pattern
		Creational design patterns abstract the instantiation process

a. Singleton-------------------------------------

The copy constructor and assignment operator are declared in private section and not defined, which means that in fact no one can use them, so no copies of Foo can be created.

Note that in C++11 this can be achieved in more straightforward way:

// this can be even in public section
Foo(Foo const&) = delete;
Foo& operator=(Foo const&) = delete;


Use singleton in thread safe :
the only guaranteed thread-safe way to do this without locking would be to initialize all your singletons before you ever start a thread.

class Singleton
{
	public:
		static Singleton* getInstance()
		{
			if( ptrSingleton == NULL )
				ptrSingleton = new Singleton();
			return ptrSingleton;
		}
		Singleton(Singleton const&) = delete;
		Singleton& operator=(Singleton const&) = delete;		
	private:
		static Singleton* ptrSingleton;
		Singleton(){}
};

Singleton* Singleton::ptrSingleton = NULL;

#include <mutex>
#include <atomic>

Double checked locking:
class Foo {
public:
    static Foo* Instance();
private:
    Foo() {}
    static atomic<Foo*> pinstance;
    static mutex m_;
};

atomic<Foo*> Foo::pinstance { nullptr };
std::mutex Foo::m_;

Foo* Foo::Instance() {
  if(pinstance == nullptr) {
    lock_guard<mutex> lock(m_);
    if(pinstance == nullptr) {
        pinstance = new Foo();
    }
  }
  return pinstance;
}

To avoid race condition while creating the singleton object!!!
If creation is not protected then its possible to occur race condition while creating singleton object, possibly each thread can create separate/multiple singleton object.
To avoid this one simple solution is-
	create/initialize singleton object before started/created any thread.
 	And define pointer object a atomic.
	This avoid all synchronization issues.

To thread-safe implementation of singleton object:
	We need to take care of below two things:
	1. Creation of mutex is thread safe
	2. Creation of singleton pointer is thread-safe
	We can do it by creating both mutex and pointer before any thread gets started/created.
	3. Define pointer as a atomic.
Atomic:
	Atomic operation that guaranteed to execute operation as a single transaction.
	std::atomic<int> x;
	How its use:
		there is a layer of cache just above the memory layer.
		So in normal case when multiple threads accessing the same variable and perform write operation on them,
		then there will be undefined state for that variable.
		When define variable as a atomic, then in such case when multiple threads accessing the same variable:
		until and unless first thread complete its operation another thread not able to perform there operation.
		result of operation of first thread will write to the main memory and then lock it and then allow other thread to access that variable.
		https://www.youtube.com/watch?v=ZQFzMfHIxng

Use:
All stateless object which needs to be a global in a module.
Object which handles the configuration file.
single DB connection shared by multiple objects as creating a separate DB connection for every object may be costly. 
Similarly, there can be a single configuration manager or error manager in an application that handles all problems 
instead of creating multiple managers.
------------------------------------------------

b. Factory
c. Factory Method
	http://www.geeksforgeeks.org/design-patterns-set-2-factory-method/
d. Abstract Factory:

Use the Abstract Factory pattern when:
	-	a system should be independent of how its products are created, composed, and represented.
	-	a system should be configured with one of multiple families of products.
	- 	a family of related product objects is designed to be used together, and
		you need to enforce this constraint.
	- 	you want to provide a class library of products, and you want to reveal
		just their interfaces, not their implementations.

Participants:
	Abstract Factory
	Concrete Factory
	Abstract Product
	Concrete Product
	Client
		
e.g.

class : APhoneFactory
----------------------
enum PHONE_FACTORY
{
	SAMSUNG,
	HTC,
	NOKIA
};
virtual IDump* GetDump()=0;
virtual ISmart* GetSmart()=0;
static APhoneFactory* CreateFactory(PHONE_FACTORY fact);

class : SAMSUNGFactory : public APhoneFactory
-----------------------------------------------
IDump* GetDump()
{return new A();}

ISmart* GetSmart()
{return new B();}

class : HTCFactory : public APhoneFactory
------------------------------------------------

class : NOKIAFactory : public APhoneFactory
------------------------------------------------

class IDump
-------------------------
virtual string Name()=0;

class ISmart
-------------------------
virtual string Name()=0;

class A : public IDump
----------------------
string Name()
{return "A";}

class B : public IDump
----------------------

class C : public IDump
----------------------

class X : public ISmart
------------------------
string Name()
{return "X";}

class Y : public ISmart
-----------------------

class Z : public ISmart
-----------------------

int main()
{
	APhoneFactory* Phone = APhoneFactory::CreateFactory(APhoneFactory::PHONE_FACTORY::SAMSUNG);
	cout<<"SAMSUNG ka Dump Phone : "<<Phone->GetDump()->Name();
}

The Abstract Factory pattern has the following benefits and liabilities:
1. It isolates concrete classes.
2. It makes exchanging product families easy.
3. It promotes consistency among products.
4. Supporting new kinds of products is difficult.

AbstractFactory classes are often implemented with factory methods (Factory Method
(121)), but they can also be implemented using Prototype (133).
A concrete factory is often a singleton (Singleton (144)).

Ref: https://www.codeproject.com/Articles/331304/Understanding-and-Implementing-Abstract-Factory
================================================================================================

e. Builder		: e.g Robot
---------------------------
https://github.com/7yadavrupesh/designpattern/blob/master/Builder%20Design%20Pattern/Builder%20Design%20Pattern%20In%20C%2B%2B.cpp

The forte of Builder is constructing a complex object step by step. An abstract base class declares the standard construction process, and concrete derived classes define the appropriate implementation for each step of the process.


f. Prototype : cloning
		
		
2. Structural Pattern
======================
Adapter	:	wrapper on lib
Bridge	:	Abstraction over implementation, e.g. data store(XML or sql)
					Bridge pattern will seperate the implementation hierarchy and Abstraction hierarchy
					So both interface and implementation hierarchy may change independently.				
e.g
				

class IColor
{
public:
    virtual string Color() = 0;
};
 
class RedColor : public IColor
{
public:
    string Color()
    {
        return "of Red Color";
    }
};
 
class BlueColor : public IColor
{
public:
    string Color()
    {
        return "of Blue Color";
    }
};
 
class ICarModel
{
public:
    virtual string WhatIsMyType() = 0;
};
 
class Model_A : public ICarModel
{
    IColor* _myColor;
public:
    Model_A(IColor *obj) :_myColor(obj){}
    string WhatIsMyType()
    {
        return "I am a Model_A " + _myColor->Color();
    }
};
 
class Model_B : public ICarModel
{
    IColor* _myColor;
public:
    Model_B(IColor *obj) :_myColor(obj){}
    string WhatIsMyType()
    {
        return "I am a Model_B " + _myColor->Color();;
    }
};
 
int main()
{
    IColor* red = new RedColor();
    IColor* blue = new BlueColor();
 
    ICarModel* modelA = new Model_B(red);
    ICarModel* modelB = new Model_A(blue);
 
    cout << "\n" << modelA->WhatIsMyType();
    cout << "\n" << modelB->WhatIsMyType() << "\n\n";
 
    delete red;
    delete blue;
    return 1;
}

				
					
		Composite:	to implement tree like structure
					class car
					|       |
					Engine  Tyre
				|    	|
			Electrical  Non-Electrical
					
		Decorator: Added additional responsible to an object dynamically.
					Coffee maker. different type of coffee (Houseblend, darkrost) with different combination(milk,mocha)
					according to different combination price and discription will change dynamically.
					
		Facade:		multiple steps combine and apper as one by facade
					Provide a unified interface to a set of interfaces in a subsystem. 
					Facade defines a higher-level interface that makes the subsystem easier to use.
					Wrap a complicated subsystem with a simpler interface.
					Event manager, use in web application.
					
		Proxy:		Provide placeholder for another object to access it. bank transaction
		Flyweight:	use sharing object while need to create large number of same objects.
				
3.	Behavioral Pattern
Chain of responsibility:
				create chain of receivers objects to handle a request
				In Qt child-parent
Observer Pattern:
				defines one to many dependency between objects so that,
				if object changed all its dependent objects notify and action perform.
				e.g. QT signal slot.

class Subject {
    // 1. "independent" functionality
    vector < class Observer * > views; // 3. Coupled only to "interface"
    int value;
  public:
    void attach(Observer *obs) {
        views.push_back(obs);
    }
    void setVal(int val) {
        value = val;
        notify();
    }
    int getVal() {
        return value;
    }
    void notify();
};

class Observer {
    // 2. "dependent" functionality
    Subject *model;
    int denom;
  public:
    Observer(Subject *mod, int div) {
        model = mod;
        denom = div;
        // 4. Observers register themselves with the Subject
        model->attach(this);
    }
    virtual void update() = 0;
  protected:
    Subject *getSubject() {
        return model;
    }
    int getDivisor() {
        return denom;
    }
};

void Subject::notify() {
  // 5. Publisher broadcasts
  for (int i = 0; i < views.size(); i++)
    views[i]->update();
} 

class DivObserver: public Observer {
  public:
    DivObserver(Subject *mod, int div): Observer(mod, div){}
    void update() {
        // 6. "Pull" information of interest
        int v = getSubject()->getVal(), d = getDivisor();
        cout << v << " div " << d << " is " << v / d << '\n';
    }
};

class ModObserver: public Observer {
  public:
    ModObserver(Subject *mod, int div): Observer(mod, div){}
    void update() {
        int v = getSubject()->getVal(), d = getDivisor();
        cout << v << " mod " << d << " is " << v % d << '\n';
    }
};

int main() {
  Subject subj;
  DivObserver divObs1(&subj, 4); // 7. Client configures the number and
  DivObserver divObs2(&subj, 3); //    type of Observers
  ModObserver modObs3(&subj, 3);
  subj.setVal(14);
}


		 Command:
				Commands like actions
				we can create class for each action and a comman interface
				
				Hotel example.......Customer....waitress...order...cook
					
					Receiver 
					Command
					Client
					Invoker
					
					{ http://www.codeproject.com/Articles/343676/Understanding-and-Implementing-the-Command-Pattern }
					
					
		Interpreter:	
					like language interpreter.
					The Interpreter pattern defines a grammatical representation for a language and an interpreter to interpret the grammar. 
					Musicians are examples of Interpreters. The pitch of a sound and its duration can be represented in musical notation on a staff. 
					This notation provides the language of music. Musicians playing the music from the score are able to reproduce 
					the original pitch and duration of each sound represented.
					
		Iterator:	like iterator in C++ STL
		Mediator:
		
=================================================================

proxy object	?
		
:: Template ::
The simple idea is to pass data type as a parameter so that we don’t need to write same code for different data types. 
For example a software company may need sort() for different data types. Rather than writing and maintaining the multiple codes, 
we can write one sort() and pass data type as a parameter.

How templates work?
	Templates are expanded at compiler time. This is like macros. The difference is, compiler does type checking before template expansion. 
	The idea is simple, source code contains only function/	class, but compiled code may contain multiple copies of same function/class.

Function Templates 
	We write a generic function that can be used for different data types. Examples of function templates are sort(), max(), min(), printArray()
	e.g.
	template <typename T> 
	T myMax(T x, T y) 
	{ 
   		return (x > y)? x: y; 
	} 
	int main() 
	{ 
  		cout << myMax<int>(3, 7) << endl;  // Call myMax for int 
  		cout << myMax<double>(3.0, 7.0) << endl; // call myMax for double 
  		cout << myMax<char>('g', 'e') << endl;   // call myMax for char 
  		return 0; 
	}


Can there be more than one arguments to templates?
	Yes, like normal parameters, we can pass more than one data types as arguments to templates. 

Can we specify default value for template arguments?
	Yes, like normal parameters, we can specify default arguments to templates
	e.g.
	template<class T, class U = char> 
	class A  { };

What is the difference between function overloading and templates?

What happens when there is static member in a template class/function?
	Each instance of a template contains its own static variable

template specialization
e.g.
1.	Normal template
template <typename T>
class Test
{};

2. specialization:
template <>
class Test<char>
{};

e.g.
template<>
class ABC<char>
{
	public:
	ABC(char a)
		cout<<"This is char"<<a<<endl;
};

template<typename T>
class ABC
{
	public:
	ABC(T a)
		cout<<"This is not char"<<a<<endl;
};

Int main()
{
	ABC<int> obj1(10);
	ABC<char> obj2('a');
}

OUTPUT:
This is not char
This is char

partial specialization	?

Difference between classname and typename
https://stackoverflow.com/questions/2023977/difference-of-keywords-typename-and-class-in-templates

=========================================== :: Advance C++11 :: ========================================
========================================================================================================
constant data members can initialise while declaration.
const int a = 10;

syntax to use C++11 features while compilation:
	g++ -std=c++11 -o output.out source.cpp

New data type: long long

:: final ::
1. prevent a virtual function from being overridden.
e.g.
	virtual void myfun() final 
    	{ 
        	cout << "myfun() in Base"; 
    	} 

2. final specifier in C++ 11 can also be used to prevent inheritance of class / struct. 
	If a class or struct is marked as final then it becomes non inheritable and it cannot be used as base class/struct.
	
	class Base final 
	{ 
	};

:: for_each ::
	vector<int> v(10);
    	for_each(v.begin(), v.end(), print);	// typical for_each
    	

    	for_each(v.begin(), v.end(), [](int& i){static int n=1;i=n++;}); // replace function print with lambda function
    
    	for_each(v.begin(), v.begin()+10, [](int i){cout<<i<<" ";});




:: auto ::
Using the auto keyword permits to spend less time having to write out things the compiler already knows.

:: unique_ptr ::

:: static_assert ::
used to test a software assertion at the compile time.
e.g.
static_assert(Size > 3, "Vector size is too small!"); 
If condition fail then assertion occurs.
error: static assertion failed: Vector size is too small!

:: override ::
In a member function declaration or definition, override ensures that the function is virtual and is overriding a virtual function from a base class. 
The program is ill-formed (a compile-time error is generated) if this is not true.

struct A
{
    virtual void foo();
    void bar();
};
 
struct B : A
{
    void foo() const override; // Error: B::foo does not override A::foo
                               // (signature mismatch)
    void foo() override; // OK: B::foo overrides A::foo
    void bar() override; // Error: A::bar is not virtual
};


::Lambda Expression::

C++ 11 introduced lambda expression to allow us write an inline function which can be used for short snippets of code that are not going to be reuse and not worth naming. In its simplest form lambda expression can be defined as follows:


[ capture clause ] (parameters) -> return-type  
{   
   definition of method   
} 

	[](){}
	[]: capture list -> all variable define above the lambda, we can pass them all by using [], [=]:send all var by value, [&]:by reference 
	(): function argument
	{}:function body
	
	Defining and calling a lambda:
	int main()
	{
		[](){
			cout<<"In Lambda function";
			}();		// () calling lambda function here
			
		return 1;
	}
	auto fun = [](){};
	
	With Function Arguments:
	int main()
	{
		int a =10;
		[a](int val){
			cout<<"In Lambda function"<<val<<a;
			}(100);		// () calling lambda function here
			
		return 1;
	}
	
	
	auto fun = [](){
				cout<<"Lambda with name";
		};
		
		// call the lambda function
		fun();
		
	std::function<> template
	
	function<void (int)> funp = [](int val){
		cout<<""<<val;
	};
	
	void(*funp)(int) = [](int val){
		cout<<""<<val;
	};

Use:
e.g. 
1.
Vector<int> v{1,2,3,4,5,6,7};
Auto it = std::find_if(v.begin(), v.end(), [](int value){return value>3};);

2.
void print(int v)
{
   cout<<v<<" "; 
}
int main()
{
    vector<int> v(10);
    for_each(v.begin(), v.end(), print);	// typical for_each
    cout<<endl;
    for_each(v.begin(), v.end(), [](int& i){static int n=1;i=n++;}); // replace function print with lambda function
    
    for_each(v.begin(), v.begin()+10, [](int i){cout<<i<<" ";});
    return 1;
}


InputIterator find_if (InputIterator first, InputIterator last, UnaryPredicate pred);
Pred: function pointer

nullptr
-------
nullptr is a replacement for the NULL. nullptr is a typesafe.
Traditional NULL is a macro having value ZERO. NULL is not typesafe.
C++11 introduces a new keyword nullptr to serve as null pointer constant.
nullptr has the type std::nullptr_t

Problem with NULL:
// function with integer argument 
int fun(int N)   { cout << "fun(int)"; } 
  
// Overloaded function with char pointer argument 
int fun(char* s)  { cout << "fun(char *)"; } 
  
int main()  
{ 
    // Ideally, it should have called fun(char *), 
    // but it causes compiler error. 
    fun(NULL);   
} 
NULL is typically defined as (void *)0 and conversion of NULL to integral types is allowed. So the function call fun(NULL) becomes ambiguous.

nullptr is a keyword that can be used at all places where NULL is expected. Like NULL, nullptr is implicitly convertible and comparable to any pointer type. Unlike NULL, 
it is not implicitly convertible or comparable to integral types.

To summarize its properties:

Property 1: It has it’s own type std::nullptr_t and
Property 2: It is implicitly convertible and comparable to any pointer type or pointer-to-member type but
Property 3: It is not implicitly convertible or comparable to integral types, except for bool


Uniform initilaization syntax
————————————————————————————— 
Initialization of dynamically allocated arrays:
int *pi = new int[5]{1, 2, 3, 4, 5};

Initialization of an array member variable:
class A {
  int arr[3];
public:
  A(int x, int y, int z) : arr{x, y, z} { };
};

Initialization of a STL container:
 std::vector v1{1, 2};


Delegating constructors C++11
------------------------------
Sometimes it is useful for a constructor to be able to call another constructor of the same class. This feature, called Constructor Delegation.

class Foo 
{
public: 
  Foo(char x, int y) {}
  Foo(int y) : Foo('a', y) {} // Foo(int) delegates to Foo(char,int)
};


Initialization order
——————————-----------

The order of member initializers in the list is irrelevant: the actual order of initialization is as follows:
1) If the constructor is for the most-derived class, virtual base classes are initialized in the order in which they appear 
	in depth-first left-to-right traversal of the base class declarations (left-to-right refers to the appearance in base-specifier lists)
2) Then, direct base classes are initialized in left-to-right order as they appear in this class's base-specifier list
3) Then, non-static data members are initialized in order of declaration in the class definition.
4) Finally, the body of the constructor is executed



Deleted and defaulted function declarations
-------------------------------------------
Deleted
--------

The C++11 standard introduced deleted function declaration as a new form of function declaration.
 
To declare a deleted function, you can append the “=delete;” specifier to the end of a function declaration. 
The compiler prohibits the usage of a deleted function. For example, 
you can declare the implicitly defined copy constructor and copy assignment operator of class X 
as deleted functions to prevent object copy of that class.

Example 2:

class X{
 public:
   X();
   X(const X&) = delete;                                      //deleted copy constructor
   X& operator = (const X &) = delete;                //deleted copy assignment operator
};
 
int main(){
  X x1;
  X x2=x1;         //Compile time Error. The usage of the copy constructor is disabled.
  X x3;
  x3=x1;            //Compile time Error. The usage of the copy assignment operator is disabled.
}

The "delete" mechanism can be used for any function. For example, we can eliminate an undesired conversion like this:

struct Z {
    // ...

    Z(long long);     // can initialize with an long long         
    Z(long) = delete; // but not anything less
};

Default
-------
This makes the compiler generate the default implementations for explicitly defaulted functions, which are more efficient than manually programmed function implementations.
whenever we declare a parameterized constructor, the compiler won’t create a default constructor. In such a case, we can use the default specifier in order to create a default one. 
class A { 
public: 
  
    // A user-defined  
    // parameterized constructor 
    A(int x)  
    { 
        cout << "This is a parameterized constructor"; 
    } 
      
    // Using the default specifier to instruct 
    // the compiler to create the default  
    // implementation of the constructor. 
    A() = default;  
}; 


Copy Elision 
————————————

Copy elision (or Copy omission) is a compiler optimization technique that avoids unnecessary copying of objects. Now a days, almost every compiler uses it. 
Let us understand it with the help of an example.

class A
{
	int _a;
public:
	A(int a) 
	{ 
		cout << "\nConstructor A(int a)\n";
		_a = a; 
		cout << _a;
	}
	A(const A& obj)
	{
		cout << "\nCopy constructor called\n";
	}
};

int main()
{
	A obj1(20)	// Constructor A(int a) called
	A obj2 = obj1;	// Copy constructor called
	A obj3 = 10;	// ***Constructor A(int a) called***
}

A obj3 = 10;	// ***Constructor A(int a) called***


According to theory, when the object “obj3” is being constructed, one argument constructor is used to convert “10” to a temporary object
 & that temporary object is copied to the object “obj3”. So the statement
A obj3 = 10;

Should be broken down by:

A obj3 = A(10);

However, most of the C++ compilers avoid such overheads of creating a temporary object & then copying it.

The modern compiler break down the statement 
A obj3 = 10;

As

A obj3(10)

and thus eliding call to copy constructor.

However, if we still want to ensure that the compiler doesn’t elide the call to copy constructor [disable the copy elision], we can compile the program using “-fno-elide-constructors” option with g++ and see the output as following:

  > g++ copy_elision.cpp -fno-elide-constructors


Other imp questions:
Can we do “delete this”?
	yes, but after deleting this pointer we can not use it. If use we get exception


::Move constructor:: 
--------------------
Class ABC
{
    int a;
	int* ptr;
	public:
	ABC(ABC& obj)		// call by reference
	{}
	ABC(ABC&& obj)		// call by rvalue reference
	{
		this->ptr = obj.ptr;
	 	obj.ptr = nulptr;
	}
};

ABC getObject()
{
	ABC obj;
	return obj;
} 
Int main()
{
	ABC obj1 = getObject();	// call by rvalue reference
}

Example:
Class ABC
{
	int* ptr;
	public:
	ABC(ABC&& obj)
	{
		this->ptr = obj.ptr;
		obj.ptr = nullptr;
	}
};

::IMP::
The compiler will not provide a default move constructor if you provide a user-defined copy constructor, assignment operator, or destructor. 
The assumption is that if you need special logic for copying or destroying the object it's likely that you will need special logic for moving as well, and simply using the default could be dangerous. If you do not, you can explicitly tell the compiler to provide the default move constructor.


Class ABC
{
	int* ptr;
 	
 	public:
		ABC(const ABC& obj)
		{
			//copy constructor
		}
		
		ABC(ABC&& obj) = default;	
};


::Move assignment operator::
The compiler will not provide a default Move assignment operator if you provide a user-defined copy constructor, assignment operator, or destructor. 
The assumption is that if you need special logic for assigning / copying or destroying the object it's likely that you will need special logic for moving as well, and simply using the default could be dangerous. If you do not, you can explicitly tell the compiler to provide the default Move assignment operator.
Class ABC
{
	int* ptr;
	public:
		ABC& operator=(ABC&& obj)
		{

		}

};




C++11 has in built int algorithms for following:
       // are all of the elements positive?
       all_of(first, first+n, ispositive()); 

      // is there at least one positive element?
      any_of(first, first+n, ispositive());

      // are none of the elements positive?
      none_of(first, first+n, ispositive()); 

Use of “and” Though not a very productive one, this tip helps you to just use conditional operator and instead of typing &.
// C++ code to demonstrate working of "and" 
#include<iostream> 
using namespace std; 
int main() 
{ 
    int a = 10; 
    if (a < 20 and a > 5) 
      cout << "Yes"; 
    return 0; 
}

*/

Other questions:
================
echniques to handle bad allocation exception
1. Exception handling
2. Allocate memory dynamically using "new" with
	//"nothrow" version of new
	char *ptr = new(std::nothrow) char[CHUNK_SIZE];						
						
						









