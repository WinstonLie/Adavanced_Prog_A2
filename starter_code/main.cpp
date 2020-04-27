#include <iostream>
#include <string>

void menuDisplay();

bool manageInput(char input);

void printCredits();

int main(void){
    std::cout << "Welcome to Azul" << std::endl;
    std::cout << "------------------" << std::endl;
    // Variable that loops main menu,
    // goes false when quitting or invalid input occurs
    bool menu_loop = true;
    while (menu_loop){
        // Displays main menu options
        menuDisplay();
        std::cout << "\n> ";
        // Inputs character from user
        char input;
        std::cin >> input;
        std::cout << std::endl;
        // If not eof then process input
        // If eof or quitting then end loop
        if (std::cin.good()){
            menu_loop = manageInput(input);
        } else {
            menu_loop = false;
        }
    }

    return EXIT_SUCCESS;
}

void menuDisplay(){
    std::cout << "\nMenu"<< std::endl;
    std::cout << "----"<< std::endl;

    std::cout << "1. New Game"<< std::endl;
    std::cout << "2. Load Game"<< std::endl;
    std::cout << "3. Credits"<< std::endl;
    std::cout << "4. Quit"<< std::endl;

}
//Checks the input
bool manageInput(char input){
    bool checked = false;
    
    //New Game
    if(input == '1'){
        std::cout << "Starting a New Game" << std::endl;
        checked = true;
    }
    //Load saved game
    else if(input == '2'){
        std::cout << "Loading Game..." << std::endl;
        checked = true;
    }
    //gets credit
    else if(input == '3'){
        printCredits();
        checked = true;
    }
    //Quit game
    else if(input == '4'){
        std::cout << "Quitting The Game" << std::endl;
        checked = false;
    }
    else{
        std::cout << "Error: Invalid Input";
        std::cout <<  std::endl;
        checked = true;
    }
    return checked;
}

void printCredits(){
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "<Student 1>" << std::endl;
    std::cout << "Name: Winston ." << std::endl;
    std::cout << "Student ID: s3777969" << std::endl;
    std::cout << "Email: s3777969@student.rmit.edu.au" << std::endl;

    std::cout << "\n<Student 2>" << std::endl;
    std::cout << "Name: Jordan Sorrenti" << std::endl;
    std::cout << "Student ID: s3782534" << std::endl;
    std::cout << "Email: s3782534@student.rmit.edu.au" << std::endl;

    std::cout << "\n<Student 3>" << std::endl;
    std::cout << "Name: Rodrigo Miguel Rojas" << std::endl;
    std::cout << "Student ID: s3784466" << std::endl;
    std::cout << "Email: s3784466@student.rmit.edu.au" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

