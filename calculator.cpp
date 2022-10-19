#include <iostream>
#include <string.h>
#include <list>
#include <math.h>
#include <string>

using namespace std;

// This is the main order of operations performed
char operators[5] = {'^', '*', '/', '+', '-'};

float addition(float a, float b){
    return a + b;
}

float subtraction(float a, float b){
    return a - b;
}

float mutliplication(float a, float b){
    return a * b;
}

float division(float a, float b){
    return float(float(a) / float(b));
}

bool contains(char ls[], char c, int len){
    /**
     * This function checks if the given char array contains the char provided.
     */
    for(int i =0; i<len; i++){
        char ele = ls[i];
        if(ele == c){
            return true;
        }
    }
    return false;
}

bool hasNumber(string s){
    char numbers[10] = {'1', '2', '3', '4', '5','6','7','8','9','0'};

    for(char n: numbers){
        if(s.find(n) != string::npos){
            return true;
        }
    }
    return false;
}

bool hasOperator(string s){
    char operators[5] = {'^', '*', '/', '+', '-'};

    for(char n: operators){
        if(s.find(n) != string::npos){
            return true;
        }
    }
    return false;
}

float performOperation(string operation, float num1, float num2){
    /*
     * This function performs the specified operation on the given numbers and returns the float result.
    */
    if(operation == "+"){
        return num1+num2;
    }else if(operation == "-"){
        return subtraction(num1, num2);
    }else if(operation == "*"){
        return mutliplication(num1, num2);
    }else if(operation == "/"){
        return division(num1, num2);
    }else if(operation == "^"){
        return pow(num1, num2);
    }

    return 0;
}

void showList(list<string> ls){
    /*
    * This method is used to display a list<string> to the console.
    */
    std::cout <<"[";
    for(string ele: ls){
        std::cout << ele << ", ";
    }
    std::cout << "]" << endl;
}

list<char> sortOperations(list<char> operations){
    list<char> sorted_operations;

    for(char c: operators){
        for(char s: operations){
            if(s == c){
                sorted_operations.push_back(s);
            }
        }
    }
    return sorted_operations;
}

list<string> removeFromList(int index, list<string> ls){
    /*
    * This function remooves the item at the given index from the list and returns the updated list.
    */
    int current_index = 0;
    int counter = 0;
    list<string> return_list;
    for(string s: ls){
        counter = counter +1;
        if(current_index != index){
            return_list.push_back(s);
        }
        current_index += 1;
    }
    return return_list;
}

list<string> replaceFromList(int index, list<string> ls, string replacement){
    int current_index = 0;
    int counter = 0;
    list<string> return_list;

    // Iterate over each element in the list
    for(string s: ls){
        counter = counter +1;

        // Check if the current index matches the index provided, if so replaces the element
        // with the replacement provided
        if(current_index != index){
            return_list.push_back(s);
        }else{
            return_list.push_back(replacement);
        }
        current_index += 1;
    }
    return return_list;
}

void DoMath(){

    // Declare the variables that will be used by the function
    std::string statement, number_string;
    char current_operator;
    int last_number, index, number_of_operations, elements;
    list<string> equation;
    list<char> operations_to_do;

    // The arrays which contain the expected characters for a calculator
    char numbers[10] = {'1', '2', '3', '4', '5','6','7','8','9','0'}; 

    // Collect the math statement from the user
    std::cout << "Enter your math experssion: ";
    cin >> statement;

    number_of_operations = 0;
    elements = 0;
    number_string = "";

    // Counts the operations and converts the equation into a list
    for(char c: statement){

        // Checks if the character is an operator
        if(contains(operators, c, 5)){

            // Gets the operator and saves the previous number
            number_of_operations += 1;
            operations_to_do.push_back(c);
            equation.push_back(number_string);
            equation.push_back(string(1, c));
            elements = elements +2;
            number_string = "";
        } 

        // Checks if the character is a number
        else if(contains(numbers,c, 10)){
            number_string += c;
        }  
    }

    // Checks to ensure that all numbers have been added to the list
    if(number_string != ""){
        equation.push_back(number_string);
        elements = elements +1;
        number_string = "";
    }

    // This gets the sorted list in which the operations should be performed
    operations_to_do = sortOperations(operations_to_do);

    // Iterates for each operation in the equation (sorted by PEMDAS priority)
    for(char c: operations_to_do){

        index = 0;
        int stop_index;
        string operation = "";
        bool has_operator = false;
        float left_number, right_number;

        // Iterates over each character in the math expression and performs the operations
        for(string ele: equation){

            // Handles when the element is a number
            if(hasNumber(ele)){
                if(!has_operator){
                    left_number = stof(ele);
                }else{
                    right_number = stof(ele);
                    break;
                }
            }
            
            // Handles when the element is an operator
            else if(hasOperator(ele)){

                // Checks if the operator is the operator that is specified in the operation order list
                if(string(1, c) == ele){
                    operation = ele;
                    stop_index = index;
                    has_operator = true;
                }else{
                    left_number = 0;
                }
            }
            index = index + 1;
        }

        // Checks to ensure a value was assgined for the left and right numbers
        if(left_number && right_number){

            int insert_index = stop_index;

            // Performs the operation on the left and the right numbers, saves the result as a float.
            float res = performOperation(operation, left_number, right_number);

            // Removes the left number and the operation from the list of operations to be performed
            equation = removeFromList(stop_index, equation);
            equation = removeFromList(stop_index, equation);

            // Removes the right number from the list and replaces it with the calculated value
            if (stop_index <2){
                equation = replaceFromList(0, equation, to_string(res));
                insert_index = 0;
            }else{
                equation = replaceFromList(stop_index-1, equation, to_string(res));
            }
        }  

        // Clear the value of the numbers
        left_number = 0;
        right_number = 0;     
    }

    // Displays the result to the console
    std::cout << statement << " = " << equation.front() << endl;
}

int main(){

    DoMath(); // This is the function which prompts the user to enter an equation

    return 0;
}