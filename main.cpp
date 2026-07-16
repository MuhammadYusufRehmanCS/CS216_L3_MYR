// Muhammad Yusuf Rehman
// CS216 lab 3

#include <iostream>
#include <string>
#include <limits>

using namespace std;

const string LAB_NAME = "CS216 Lab 3";
const string STUDENT_NAME = "Muhammad Yusuf Rehman";

const int TEST_WHOLE = 2;
const int TEST_NUMERATOR = 3;
const int TEST_DENOMINATOR = 4;
const int TEST_NEW_NUMERATOR = 5;
const int NEGATIVE_NUMERATOR = -3;
const int NEGATIVE_DENOMINATOR = -4;
const int NEGATIVE_WHOLE = -2;
const int IMPROPER_WHOLE = 5;
const int IMPROPER_NUMERATOR = 7;
const int IMPROPER_DENOMINATOR = 3;
const string DENOMINATOR_ZERO_MESSAGE = "The denominator cannot be zero.";
const string NUMERATOR_ZERO_MESSAGE = "The numerator cannot be zero.";
const string NUMERATOR_NEGATIVE_MESSAGE = "The numerator cannot be negative.";
const string DENOMINATOR_NEGATIVE_MESSAGE = "The denominator cannot be negative.";
const string WHOLE_NEGATIVE_MESSAGE = "The whole number cannot be negative.";
const string INVALID_MIXED_FRACTION_MESSAGE = "The numerator cannot be greater than the denominator when the whole number is greater than zero.";
const string UNKNOWN_ERROR_MESSAGE = "An unknown fraction error occurred.";
const string NO_ERROR_MESSAGE = "No fraction error.";
const string INPUT_ERROR_MESSAGE = "Invalid menu choice.";

enum MenuOption
{
    INVALID_CHOICE = 0,
    DEMO,
    QUIT
};

enum FractionError
{
    DENOMINATOR_ZERO,
    NUMERATOR_ZERO,
    NUMERATOR_NEGATIVE,
    DENOMINATOR_NEGATIVE,
    WHOLE_NEGATIVE,
    INVALID_MIXED_FRACTION,
    UNKNOWN_FRACTION_ERROR
};

class FractionException
{
private:
    string errorMessage = UNKNOWN_ERROR_MESSAGE;

public:
    explicit FractionException(FractionError error = UNKNOWN_FRACTION_ERROR);

    string getMessage() const;
};

class Fraction
{
private:
    int numerator = 1;
    int denominator = 1;
    bool lastOperationSuccessful = true;
    string lastErrorMessage = NO_ERROR_MESSAGE;

    static int fractionCount;
    static const int DEFAULT_NUMERATOR = 1;
    static const int DEFAULT_DENOMINATOR = 1;

public:
    Fraction();
    Fraction(const Fraction& otherFraction);
    Fraction(int newNumerator);
    Fraction(int newNumerator, int newDenominator);
    Fraction(int whole, int newNumerator, int newDenominator);
    ~Fraction();

    void setNumerator(int newNumerator);
    void setDenominator(int newDenominator);
    void setFraction(int newNumerator);
    void setFraction(int newNumerator, int newDenominator);
    void setFraction(int whole, int newNumerator, int newDenominator);

    string getLastErrorMessage() const;
    bool wasLastOperationSuccessful() const;
    string toString() const;
    void print() const;

    static int getFractionCount();
};

void displayMenu();
MenuOption getMenuChoice();
void clearCin(const string& errorMessage);
void runDemo();
void demonstrateValidFractions();
void testZeroDenominator();
void testZeroNumerator();
void testNegativeNumerator();
void testNegativeDenominator();
void testNegativeWholeNumber();
void testInvalidMixedFraction();
void testUnknownError();
void printErrorIfNeeded(const Fraction& fraction);

/*
Description:
    Runs the menu-driven Fraction class demonstration.

Pre-condition:
    The program has started.

Post-condition:
    Fraction class demonstrations are performed until the user quits.
*/
int main()
{
    MenuOption choice = INVALID_CHOICE;

    cout << LAB_NAME << '\n'
         << STUDENT_NAME << '\n';

    do
    {
        displayMenu();
        choice = getMenuChoice();

        switch (choice)
        {
            case DEMO:
                runDemo();
                break;

            case QUIT:
                cout << "\nFraction class demonstration ended.\n";
                break;

            default:
                clearCin(INPUT_ERROR_MESSAGE);
                break;
        }
    }
    while (choice != QUIT);

    return 0;
}

int Fraction::fractionCount = 0;

/*
Description:
    Creates a FractionException with an appropriate error message.

Pre-condition:
    error contains a FractionError value.

Post-condition:
    The FractionException contains an error message.
*/
FractionException::FractionException(FractionError error)
{
    switch (error)
    {
        case DENOMINATOR_ZERO:
            errorMessage = DENOMINATOR_ZERO_MESSAGE;
            break;

        case NUMERATOR_ZERO:
            errorMessage = NUMERATOR_ZERO_MESSAGE;
            break;

        case NUMERATOR_NEGATIVE:
            errorMessage = NUMERATOR_NEGATIVE_MESSAGE;
            break;

        case DENOMINATOR_NEGATIVE:
            errorMessage = DENOMINATOR_NEGATIVE_MESSAGE;
            break;

        case WHOLE_NEGATIVE:
            errorMessage = WHOLE_NEGATIVE_MESSAGE;
            break;

        case INVALID_MIXED_FRACTION:
            errorMessage = INVALID_MIXED_FRACTION_MESSAGE;
            break;

        case UNKNOWN_FRACTION_ERROR:
            errorMessage = UNKNOWN_ERROR_MESSAGE;
            break;

        default:
            errorMessage = UNKNOWN_ERROR_MESSAGE;
            break;
    }
}

/*
Description:
    Returns the FractionException error message.

Pre-condition:
    A FractionException object exists.

Post-condition:
    The stored error message is returned.
*/
string FractionException::getMessage() const
{
    return errorMessage;
}

/*
Description:
    Creates a Fraction with default values.

Pre-condition:
    None.

Post-condition:
    A valid Fraction with default values exists and the Fraction
    object count is increased.
*/
Fraction::Fraction()
{
    setFraction(DEFAULT_NUMERATOR, DEFAULT_DENOMINATOR);
    fractionCount++;
}

/*
Description:
    Creates a copy of an existing Fraction.

Pre-condition:
    otherFraction is a valid Fraction.

Post-condition:
    A valid copy exists and the Fraction object count is increased.
*/
Fraction::Fraction(const Fraction& otherFraction)
{
    setFraction(otherFraction.numerator, otherFraction.denominator);
    fractionCount++;
}

/*
Description:
    Creates a Fraction using one numerator argument.

Pre-condition:
    newNumerator is intended to represent a positive numerator.

Post-condition:
    A valid Fraction exists and the Fraction object count is increased.
*/
Fraction::Fraction(int newNumerator)
{
    setFraction(newNumerator, DEFAULT_DENOMINATOR);
    fractionCount++;
}

/*
Description:
    Creates a Fraction using a numerator and denominator.

Pre-condition:
    The supplied values are intended to represent a positive Fraction.

Post-condition:
    A valid Fraction exists and the Fraction object count is increased.
*/
Fraction::Fraction(int newNumerator, int newDenominator)
{
    setFraction(newNumerator, newDenominator);
    fractionCount++;
}

/*
Description:
    Creates a Fraction using a whole number, numerator, and denominator.

Pre-condition:
    The supplied values are intended to represent a positive Fraction.

Post-condition:
    A valid Fraction exists and the Fraction object count is increased.
*/
Fraction::Fraction(int whole, int newNumerator, int newDenominator)
{
    setFraction(whole, newNumerator, newDenominator);
    fractionCount++;
}

/*
Description:
    Destroys a Fraction and updates the Fraction object count.

Pre-condition:
    A Fraction object exists.

Post-condition:
    The numerator and denominator are set to 0/1 and the Fraction
    object count is decreased.
*/
Fraction::~Fraction()
{
    numerator = 0;
    denominator = DEFAULT_DENOMINATOR;
    fractionCount--;
}

/*
Description:
    Attempts to change the numerator of a Fraction.

Pre-condition:
    A valid Fraction object exists.

Post-condition:
    The numerator is changed only when the proposed Fraction is valid.
*/
void Fraction::setNumerator(int newNumerator)
{
    setFraction(newNumerator, denominator);
}

/*
Description:
    Attempts to change the denominator of a Fraction.

Pre-condition:
    A valid Fraction object exists.

Post-condition:
    The denominator is changed only when the proposed Fraction is valid.
*/
void Fraction::setDenominator(int newDenominator)
{
    setFraction(numerator, newDenominator);
}

/*
Description:
    Attempts to set a Fraction using one numerator argument.

Pre-condition:
    A valid Fraction object exists.

Post-condition:
    The Fraction is changed only when the proposed value is valid.
*/
void Fraction::setFraction(int newNumerator)
{
    setFraction(newNumerator, DEFAULT_DENOMINATOR);
}

/*
Description:
    Attempts to set a Fraction using a numerator and denominator.

Pre-condition:
    A valid Fraction object exists.

Post-condition:
    The Fraction is changed only when the proposed values are valid.
*/
void Fraction::setFraction(int newNumerator, int newDenominator)
{
    setFraction(0, newNumerator, newDenominator);
}
/*
Description:
    Validates and stores a whole number, numerator, and denominator.

Pre-condition:
    A valid Fraction object exists.

Post-condition:
    Valid values are stored in the Fraction. If a value is invalid,
    the Fraction remains unchanged and the error message is stored.
*/
void Fraction::setFraction(int whole, int newNumerator, int newDenominator)
{
    int proposedNumerator = numerator;
    int proposedDenominator = denominator;

    lastOperationSuccessful = false;
    lastErrorMessage = UNKNOWN_ERROR_MESSAGE;

    try
    {
        if (newDenominator == 0)
        {
            throw FractionException(DENOMINATOR_ZERO);
        }
        else if (newNumerator == 0)
        {
            throw FractionException(NUMERATOR_ZERO);
        }
        else if (newNumerator < 0)
        {
            throw FractionException(NUMERATOR_NEGATIVE);
        }
        else if (newDenominator < 0)
        {
            throw FractionException(DENOMINATOR_NEGATIVE);
        }
        else if (whole < 0)
        {
            throw FractionException(WHOLE_NEGATIVE);
        }
        else if (whole > 0 && newNumerator > newDenominator)
        {
            throw FractionException(INVALID_MIXED_FRACTION);
        }
        else
        {
            proposedNumerator = whole * newDenominator + newNumerator;
            proposedDenominator = newDenominator;
            numerator = proposedNumerator;
            denominator = proposedDenominator;
            lastOperationSuccessful = true;
            lastErrorMessage = NO_ERROR_MESSAGE;
        }
    }
    catch (const FractionException& error)
    {
        lastErrorMessage = error.getMessage();
    }
}
/*
Description:
    Returns the last Fraction error message.

Pre-condition:
    A Fraction object exists.

Post-condition:
    The stored error message is returned.
*/
string Fraction::getLastErrorMessage() const
{
    return lastErrorMessage;
}

/*
Description:
    Reports whether the last Fraction operation succeeded.

Pre-condition:
    A Fraction object exists.

Post-condition:
    true is returned if the last operation succeeded.
*/
bool Fraction::wasLastOperationSuccessful() const
{
    return lastOperationSuccessful;
}

/*
Description:
    Converts a Fraction to a formatted string.

Pre-condition:
    A valid Fraction object exists.

Post-condition:
    The Fraction is returned as a formatted string.
*/
string Fraction::toString() const
{
    int whole = numerator / denominator;
    int remainder = numerator % denominator;
    string fractionString =
        to_string(numerator) + "/" + to_string(denominator);

    if (whole > 0 && remainder > 0)
    {
        fractionString =
            to_string(whole) + " " + to_string(remainder) +
            "/" + to_string(denominator);
    }
    else if (whole > 0)
    {
        fractionString = to_string(whole);
    }

    return fractionString;
}

/*
Description:
    Prints a Fraction by calling toString.

Pre-condition:
    A valid Fraction object exists.

Post-condition:
    The formatted Fraction is displayed.
*/
void Fraction::print() const
{
    cout << toString();
}

/*
Description:
    Returns the number of Fraction objects currently in memory.

Pre-condition:
    None.

Post-condition:
    The current Fraction object count is returned.
*/
int Fraction::getFractionCount()
{
    return fractionCount;
}

/*
Description:
    Displays the Fraction class test menu.

Pre-condition:
    The output stream is available.

Post-condition:
    The menu is displayed.
*/
void displayMenu()
{
    cout << "\n\nFraction Class Test Menu\n"
            "1 Demo\n"
            "2 Quit\n";
}

/*
Description:
    Reads a menu choice.

Pre-condition:
    The input stream is available.

Post-condition:
    A MenuOption value is returned.
*/
MenuOption getMenuChoice()
{
    int numericChoice = INVALID_CHOICE;

    cout << "Enter your choice: ";
    cin >> numericChoice;

    if (cin.fail())
    {
        numericChoice = INVALID_CHOICE;
    }

    return static_cast<MenuOption>(numericChoice);
}

/*
Description:
    Clears the input stream and displays an input error message.

Pre-condition:
    The input stream is available and errorMessage contains a message.

Post-condition:
    The input stream is ready for new input and the message is displayed.
*/
void clearCin(const string& errorMessage)
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << errorMessage << '\n';
}

/*
Description:
    Runs all Fraction demonstrations.

Pre-condition:
    The Fraction class is available.

Post-condition:
    All required Fraction demonstrations are displayed.
*/
void runDemo()
{
    demonstrateValidFractions();
    testZeroDenominator();
    testZeroNumerator();
    testNegativeNumerator();
    testNegativeDenominator();
    testNegativeWholeNumber();
    testInvalidMixedFraction();
    testUnknownError();
}

/*
Description:
    Demonstrates valid Fraction operations and the strong exception
    guarantee.

Pre-condition:
    The Fraction class is available.

Post-condition:
    Constructors, setters, accessors, copying, object counting, and
    preservation of a Fraction after an exception are demonstrated.
*/
void demonstrateValidFractions()
{
    cout << "\nObjects before demonstration: "
         << Fraction::getFractionCount() << "\n\n";

    {
        Fraction defaultFraction;
        Fraction oneArgumentFraction(TEST_NEW_NUMERATOR);
        Fraction twoArgumentFraction(TEST_NUMERATOR, TEST_DENOMINATOR);
        Fraction threeArgumentFraction(
            TEST_WHOLE,
            TEST_NUMERATOR,
            TEST_DENOMINATOR
        );
        Fraction copiedFraction(threeArgumentFraction);

        cout << "Default constructor: ";
        defaultFraction.print();
        cout << "\nOne-argument constructor: ";
        oneArgumentFraction.print();
        cout << "\nTwo-argument constructor: ";
        twoArgumentFraction.print();
        cout << "\nThree-argument constructor: ";
        threeArgumentFraction.print();
        cout << "\nCopy constructor: ";
        copiedFraction.print();

        defaultFraction.setNumerator(TEST_NEW_NUMERATOR);
        cout << "\nAfter setNumerator: ";
        defaultFraction.print();

        defaultFraction.setDenominator(TEST_DENOMINATOR);
        cout << "\nAfter setDenominator: ";
        defaultFraction.print();

        defaultFraction.setFraction(TEST_NEW_NUMERATOR);
        cout << "\nAfter one-argument setFraction: ";
        defaultFraction.print();

        defaultFraction.setFraction(TEST_NUMERATOR, TEST_DENOMINATOR);
        cout << "\nAfter two-argument setFraction: ";
        defaultFraction.print();

        defaultFraction.setFraction(
            TEST_WHOLE,
            TEST_NUMERATOR,
            TEST_DENOMINATOR
        );
        cout << "\nAfter three-argument setFraction: ";
        defaultFraction.print();

        cout << "\n\nTesting strong exception guarantee\n"
                "Fraction before invalid change: ";
        twoArgumentFraction.print();
        cout << '\n';

        try
        {
            twoArgumentFraction.setDenominator(0);
        }
        catch (const FractionException& error)
        {
            cout << "Fraction exception: " << error.getMessage() << '\n';
        }

        cout << "Fraction after invalid change: ";
        twoArgumentFraction.print();
        cout << "\nObjects during demonstration: "
             << Fraction::getFractionCount() << '\n';
    }

    cout << "Objects after demonstration: "
         << Fraction::getFractionCount() << '\n';
}

/*
Description:
    Demonstrates the zero-denominator exception.

Pre-condition:
    The Fraction class is available.

Post-condition:
    The exception and object counts are displayed.
*/
void testZeroDenominator()
{
    demonstrateException(ZERO_DENOMINATOR);
}

/*
Description:
    Demonstrates the zero-numerator exception.

Pre-condition:
    The Fraction class is available.

Post-condition:
    The exception and object counts are displayed.
*/
void testZeroNumerator()
{
    demonstrateException(ZERO_NUMERATOR);
}

/*
Description:
    Demonstrates the negative-numerator exception.

Pre-condition:
    The Fraction class is available.

Post-condition:
    The exception and object counts are displayed.
*/
void testNegativeNumerator()
{
    demonstrateException(NEGATIVE_NUMERATOR_TEST);
}

/*
Description:
    Demonstrates the negative-denominator exception.

Pre-condition:
    The Fraction class is available.

Post-condition:
    The exception and object counts are displayed.
*/
void testNegativeDenominator()
{
    demonstrateException(NEGATIVE_DENOMINATOR_TEST);
}

/*
Description:
    Demonstrates the negative-whole-number exception.

Pre-condition:
    The Fraction class is available.

Post-condition:
    The exception and object counts are displayed.
*/
void testNegativeWholeNumber()
{
    demonstrateException(NEGATIVE_WHOLE_TEST);
}

/*
Description:
    Demonstrates the invalid-mixed-fraction exception.

Pre-condition:
    The Fraction class is available.

Post-condition:
    The exception and object counts are displayed.
*/
void testInvalidMixedFraction()
{
    demonstrateException(IMPROPER_FRACTION);
}

/*
Description:
    Demonstrates the unknown Fraction exception.

Pre-condition:
    The FractionException class is available.

Post-condition:
    The exception and object counts are displayed.
*/
void testUnknownError()
{
    demonstrateException(UNKNOWN_ERROR_TEST);
}

/*
Description:
    Demonstrates a selected Fraction exception using hard-coded values.

Pre-condition:
    choice identifies an exception demonstration.

Post-condition:
    The selected exception is caught and displayed, and the Fraction
    object count is displayed before and after the demonstration.
*/
void demonstrateException(MenuOption choice)
{
    cout << "\nObjects before exception demonstration: "
         << Fraction::getFractionCount() << '\n';

    try
    {
        switch (choice)
        {
            case ZERO_DENOMINATOR:
            {
                Fraction testFraction(TEST_NUMERATOR, 0);
                break;
            }

            case ZERO_NUMERATOR:
            {
                Fraction testFraction(0, TEST_DENOMINATOR);
                break;
            }

            case NEGATIVE_NUMERATOR_TEST:
            {
                Fraction testFraction(
                    NEGATIVE_NUMERATOR,
                    TEST_DENOMINATOR
                );
                break;
            }

            case NEGATIVE_DENOMINATOR_TEST:
            {
                Fraction testFraction(
                    TEST_NUMERATOR,
                    NEGATIVE_DENOMINATOR
                );
                break;
            }

            case NEGATIVE_WHOLE_TEST:
            {
                Fraction testFraction(
                    NEGATIVE_WHOLE,
                    TEST_NUMERATOR,
                    TEST_DENOMINATOR
                );
                break;
            }

            case IMPROPER_FRACTION:
            {
                Fraction testFraction(
                    IMPROPER_WHOLE,
                    IMPROPER_NUMERATOR,
                    IMPROPER_DENOMINATOR
                );
                break;
            }

            case UNKNOWN_ERROR_TEST:
                throw FractionException(UNKNOWN_FRACTION_ERROR);

            default:
                throw FractionException(UNKNOWN_FRACTION_ERROR);
        }
    }
    catch (const FractionException& error)
    {
        cout << "Fraction exception: " << error.getMessage() << '\n';
    }

    cout << "Objects after exception demonstration: "
         << Fraction::getFractionCount() << '\n';
}

/*
Sample Test Run:
CS216 Lab 3
Muhammad Yusuf Rehman


Fraction Class Test Menu
1 Demonstrate valid Fractions
2 Test zero denominator
3 Test zero numerator
4 Test negative numerator
5 Test negative denominator
6 Test negative whole number
7 Test invalid mixed fraction
8 Test unknown error
9 Quit
Enter your choice: ok
Invalid menu choice.
Enter your choice: 0
Invalid menu choice.
Enter your choice: huh?
Invalid menu choice.
Enter your choice: 1

Objects before demonstration: 0

Default constructor: 1
One-argument constructor: 5
Two-argument constructor: 3/4
Three-argument constructor: 2 3/4
Copy constructor: 2 3/4
After setNumerator: 5
After setDenominator: 1 1/4
After one-argument setFraction: 5
After two-argument setFraction: 3/4
After three-argument setFraction: 2 3/4

Testing strong exception guarantee
Fraction before invalid change: 3/4
Fraction exception: The denominator cannot be zero.
Fraction after invalid change: 3/4
Objects during demonstration: 5
Objects after demonstration: 0


Fraction Class Test Menu
1 Demonstrate valid Fractions
2 Test zero denominator
3 Test zero numerator
4 Test negative numerator
5 Test negative denominator
6 Test negative whole number
7 Test invalid mixed fraction
8 Test unknown error
9 Quit
Enter your choice: 2

Objects before exception demonstration: 0
Fraction exception: The denominator cannot be zero.
Objects after exception demonstration: 0


Fraction Class Test Menu
1 Demonstrate valid Fractions
2 Test zero denominator
3 Test zero numerator
4 Test negative numerator
5 Test negative denominator
6 Test negative whole number
7 Test invalid mixed fraction
8 Test unknown error
9 Quit
Enter your choice: 3

Objects before exception demonstration: 0
Fraction exception: The numerator cannot be zero.
Objects after exception demonstration: 0


Fraction Class Test Menu
1 Demonstrate valid Fractions
2 Test zero denominator
3 Test zero numerator
4 Test negative numerator
5 Test negative denominator
6 Test negative whole number
7 Test invalid mixed fraction
8 Test unknown error
9 Quit
Enter your choice: 4

Objects before exception demonstration: 0
Fraction exception: The numerator cannot be negative.
Objects after exception demonstration: 0


Fraction Class Test Menu
1 Demonstrate valid Fractions
2 Test zero denominator
3 Test zero numerator
4 Test negative numerator
5 Test negative denominator
6 Test negative whole number
7 Test invalid mixed fraction
8 Test unknown error
9 Quit
Enter your choice: 5

Objects before exception demonstration: 0
Fraction exception: The denominator cannot be negative.
Objects after exception demonstration: 0


Fraction Class Test Menu
1 Demonstrate valid Fractions
2 Test zero denominator
3 Test zero numerator
4 Test negative numerator
5 Test negative denominator
6 Test negative whole number
7 Test invalid mixed fraction
8 Test unknown error
9 Quit
Enter your choice: 6

Objects before exception demonstration: 0
Fraction exception: The whole number cannot be negative.
Objects after exception demonstration: 0


Fraction Class Test Menu
1 Demonstrate valid Fractions
2 Test zero denominator
3 Test zero numerator
4 Test negative numerator
5 Test negative denominator
6 Test negative whole number
7 Test invalid mixed fraction
8 Test unknown error
9 Quit
Enter your choice: 7

Objects before exception demonstration: 0
Fraction exception: The numerator cannot be greater than the denominator when the whole number is greater than zero.
Objects after exception demonstration: 0


Fraction Class Test Menu
1 Demonstrate valid Fractions
2 Test zero denominator
3 Test zero numerator
4 Test negative numerator
5 Test negative denominator
6 Test negative whole number
7 Test invalid mixed fraction
8 Test unknown error
9 Quit
Enter your choice: 8

Objects before exception demonstration: 0
Fraction exception: An unknown fraction error occurred.
Objects after exception demonstration: 0


Fraction Class Test Menu
1 Demonstrate valid Fractions
2 Test zero denominator
3 Test zero numerator
4 Test negative numerator
5 Test negative denominator
6 Test negative whole number
7 Test invalid mixed fraction
8 Test unknown error
9 Quit
Enter your choice: 9

Fraction class demonstration ended.
*/