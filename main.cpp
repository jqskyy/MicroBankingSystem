#include <iostream>
#include <map>

struct Account {
    std::string id;
    std::string passwd;
    std::string cvv;
    int balance = 0;
    std::map<std::string, int> transactionHistory;
};

void displayMenu() {
    std::cout << "========== MENU ==========" << std::endl;
    std::cout << "[1] Stan konta" << std::endl;
    std::cout << "[2] Wplata srodkow" << std::endl;
    std::cout << "[3] Wyplata srodkow" << std::endl;
    std::cout << "[4] Historia transakcji" << std::endl;
    std::cout << "[5] Wyloguj" << std::endl;
    std::cout << "========== MENU ==========" << std::endl;
}

int choice() {
    displayMenu();

    int userChoice;

    std::cout << "Wybierz opcje [1-5]: ";
    std::cin >> userChoice;

    return userChoice;
}

bool loggingIn(Account &acc) {
    int attempts = 0;

    std::string id;
    std::string passwd;

    std::cout << "==========================================" << std::endl;
    std::cout << "Prosimy zalogowac sie do konta bankowego" << std::endl;
    std::cout << "==========================================" << std::endl;

    while(true){
        if(attempts == 3) {
            std::cout << "====================================================" << std::endl;
            std::cout << "Przekroczono liczbe dozwolonych prob logowania!" << std::endl;
            std::cout << "====================================================" << std::endl;
            return false;
        }

        std::cout << "Identyfikator: ";
        std::cin >> id;

        std::cout << "Haslo: ";
        std::cin >> passwd;

        if(id == acc.id && passwd == acc.passwd) {
            std::cout << "Logowanie zakonczone powodzeniem!" << std::endl << std::endl;
            return true;
        } else {
            std::cout << "Nieprawidlowy identyfikator lub haslo! Wprowadz poprawne dane!" << std::endl << std::endl;
            attempts++;
            continue;
        }
    }
}

void displayBalance(Account &acc) {
    std::cout << std::endl << "Dostepne srodki: " << acc.balance << "pln" << std::endl << std::endl;
}

void deposit(Account &acc) {
    int amount;

    std::cout << std::endl << "Podaj kwote wplaty: ";
    std::cin >> amount;

    acc.balance += amount;
    std::cout << "Pomyslnie wplacono " << amount << "pln" << std::endl << std::endl;

    acc.transactionHistory.insert(std::pair<std::string, int>("DEPOSIT", amount));
}

void withdraw(Account &acc) {
    std::string cvv;
    int amount;
    int counter = 0;

    if(acc.balance <= 0) {
        std::cout << std::endl << "Nie mozemy zrealizowac wyplaty, gdyz nie posiadasz srodkow na koncie!" << std::endl << std::endl;
        return;
    }

    while(true) {
        if(counter == 3) {
            std::cout << "Przekroczono liczbe prob weryfikacji! Twoje konto zostaje tymczasowo zablokowane!" << std::endl;
            exit(211);
        }

        std::cout << "Aby wyplacic srodki prosimy wprowadzic kod CVV: ";
        std::cin >> cvv;

        if(cvv == acc.cvv) {
            std::cout << "Weryfikacja przebiegla pomyslnie!" << std::endl << std::endl;
            break;
        } else {
            std::cout << "Wprowadzony kod CVV jest nieprawidlowy!" << std::endl << std::endl;
            counter++;
            continue;
        }

    }

    while(true) {
        std::cout << std::endl << "Podaj kwote wyplaty: ";
        std::cin >> amount;

        if(amount > acc.balance) {
            std::cout << "Nie masz wystarczajacych srodkow do zrealizowania wyplaty!" << std::endl;
            std::cout << "Twoje saldo wynosi: " << acc.balance << "pln" << std::endl << std::endl;
            break;
        } else {
            acc.balance -= amount;
            std::cout << "Pomyslnie wyplacono " << amount << "pln" << std::endl << std::endl;
            acc.transactionHistory.insert(std::pair<std::string, int>("WITHDRAW", amount));
            break;
        }
    }
}

void transactionHistory(Account &acc) {
    if(acc.transactionHistory.empty()) {
        std::cout << std::endl << "Nie posiadasz dokonanych transakcji na swoim koncie!" << std::endl << std::endl;
    } else {
        std::cout << std::endl << "=================== HISTORIA TRANSAKCJI ===================" << std::endl;
        for(auto & it : acc.transactionHistory) {
            std::cout << "Typ transakcji: " << it.first << std::endl << "Kwota: " << it.second << " pln" << std::endl << std::endl;
        }
        std::cout << "=================== HISTORIA TRANSAKCJI ===================" << std::endl << std::endl;
    }

}

int main() {
    Account acc("123456", "xyz", "6670");

    bool isUserLoggedIn = loggingIn(acc);

    while(true) {
        if(isUserLoggedIn) {
            int userChoice = choice();

            switch(userChoice) {
                case 1:
                    displayBalance(acc);
                    break;
                case 2:
                    deposit(acc);
                    break;
                case 3:
                    withdraw(acc);
                    break;
                case 4:
                    transactionHistory(acc);
                    break;
                case 5:
                    exit(0);
                default:
                    std::cout << "Nieprawidlowa wartosc! Wybierz opcje [1-5]" << std::endl;
                    break;
            }
        } else {
            std::exit(0);
        }
    }
}


// Do naprawienia historia transakcji (nie wyswietla prawidlowo wszystkich dokonanych transakcji na koncie)