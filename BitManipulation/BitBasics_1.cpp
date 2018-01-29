#include <iostream>
#include <bitset>

// Other things to see - 
// 1. XOR and a^b = (a | b) & (~a | ~b)

// MACRO DEFINITION EXAMPLES : 
// Watch for syntax - #define MACRO(a,b) (a>b...)

#define MAX_INT(a, b)     ((((int)(a)) > (int)(b)) ? (a) : (b))
#define MAX_UINT(a, b)    ((((unsigned int)(a) > (unsigned int)(b)) ? (a) : (b) ))
#define IS_BIT_SET(Num, bit)  (((Num & (0x1 << bit))? true : false))

typedef unsigned int uint;

class Bits;

class Bits
{

  public:

    // Can be unsigned too 

    Bits(int Number);

    ~Bits();

    void NumberOfBits_Brute();

    void NumberOfBits_Algo();

    int MultiplyByTwo();

    int DivideByTwo();

  private:

    int   mNumber;
};

Bits::Bits(int Number) : mNumber(Number)
{

}

Bits::~Bits()
{

}

// Irrespective of Positive/Negative/Float
// Brute force approach
void Bits::NumberOfBits_Brute()
{
    int Count = 0;

    // Note : Copy the variable as we may lose it in the next step
    int Num = mNumber;

    if(Num >= 0)
    {
        while(Num)
        {
            if(Num & 0x1)
              Count++;
            Num = Num >> 1;
        }
    }
    else
    {
        while(Num)
        {
            if(Num & (0x1 <<(8 * sizeof(int) - 1)))
              Count++;
            Num = Num << 1;
            // std::cout << " : " << std::bitset<32>(Num) << std::dec << std::endl;
        }
    }

    std::cout << " The Number of Bits for Number : " \
              << mNumber << " is : " << Count << std::endl;

    return;
}

// This Method is used to count the number of bits set using Brian Kernighan's algo
// Subtract number by 1 (n-1) and bitwise AND it with (n), store in n, increment counter till n is 0
void Bits::NumberOfBits_Algo()
{
    // Important to check for 0!
    if(mNumber == 0)
    {
        return;
    }
    
    int Num   = mNumber;
    int Count = 0;
    while(Num)
    {
        Num &= (Num - 1);
        Count++;
    }
    
    std::cout << " The Number of Bits for Number : " \
              << mNumber << " is : " << Count << std::endl;

} // NumberOfBits_Algo

// To Multiply by 2, Left shift by 1
int Bits::MultiplyByTwo()
{
    if(mNumber == 0)
      return 0;

    return mNumber << 1;
} // MultiplyByTwo

// To Divide by 2, Right shift bit by 1
int Bits::DivideByTwo()
{
    if(mNumber == 0)
    {
        return 0;
    }
    return mNumber >> 1;
} // DivideByTwo

int main(int argc, char* argv[])
{
    Bits* Num1 = new Bits(0);
    Num1->NumberOfBits_Brute();

    Bits* Num2 = new Bits(101);
    Num2->NumberOfBits_Brute();

    Bits* Num3= new Bits(-0xFFF);
    Num3->NumberOfBits_Brute();
    Num3->NumberOfBits_Algo();

    if(MAX_INT(3,2) == 3)
    {
        std::cout << " MAx is 3 " << std::endl;
    }

    if(IS_BIT_SET(0b1110, 3))
    {
        std::cout << " Bit 3 is set " << std::endl; 
    }

    return 0; 
}
