#pragma once
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsBankClient.h"

clsBankClient Client = clsBankClient::Find("");

class clsAtmMainScreen : protected clsScreen
{
private:
    enum enAtmOperation {eDeposit = 1, eWithdraw = 2, eTransfer = 3, eBalance = 4, eLogout = 5};

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

    static float _ReadAmount(clsBankClient SourceClient)
    {
        float Amount;

        cout << "\nEnter Transfer Amount? ";

        Amount = clsInputValidate::ReadFloatNumber();

        while (Amount > SourceClient.AccountBalance)
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadDblNumber();
        }
        return Amount;
    }
    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }
    static string _ReadPinCode()
    {
        string PinCode = "";
        cout << "\nPlease enter PinCode? ";
        PinCode = clsInputValidate::ReadString();
        return PinCode;
    }

    static void _Deposit() {
        double Amount = 0;
        cout << "\nPlease enter deposit amount? ";
        Amount = clsInputValidate::ReadDblNumber();

        cout << "\nAre you sure you want to perform this transaction?[y/n] ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            Client.Deposit(Amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance Is: " << Client.AccountBalance;

        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }

    static void _Withdraw() {
        double Amount = 0;
        cout << "\nPlease enter Withdraw amount? ";
        Amount = clsInputValidate::ReadDblNumber();

        cout << "\nAre you sure you want to perform this transaction?[y/n] ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (Client.Withdraw(Amount))
            {
                cout << "\nAmount Withdrew Successfully.\n";
                cout << "\nNew Balance Is: " << Client.AccountBalance;
            }
            else
            {
                cout << "\nCannot withdraw, Insuffecient Balance!\n";
                cout << "\nAmout to withdraw is: " << Amount;
                cout << "\nYour Balance is: " << Client.AccountBalance;

            }
        }
    }

    static void _Transfer() {
        string AccountNumber;
        cout << "\nPlease Enter Account Number to Transfer To: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient DestinationClient = clsBankClient::Find(AccountNumber);
        _PrintClient(DestinationClient);

        float Amount = _ReadAmount(Client);
        
        cout << "\nAre you sure you want to perform this operation? y/n? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            if (Client.Transfer(Amount, DestinationClient, "ATM"))
            {
                cout << "\nTransfer done successfully\n";
            }
            else
            {
                cout << "\nTransfer Faild \n";
            }
        }

        _PrintClient(Client);
        _PrintClient(DestinationClient);
    }

    static void _Balance() {
        _PrintClient(Client);
    }

    static void _Logout() {

    }

    static void _PerformAtmOperation(enAtmOperation Operation) {
        switch (Operation) {
        case enAtmOperation::eDeposit:
            system("cls");
            _Deposit();
            _GoBackToAtmMenuScreen();
            break;
        case enAtmOperation::eWithdraw:
            system("cls");
            _Withdraw();
            _GoBackToAtmMenuScreen();
            break;
        case enAtmOperation::eTransfer:
            system("cls");
            _Transfer();
            _GoBackToAtmMenuScreen();
            break;
        case enAtmOperation::eBalance:
            system("cls");
            _Balance();
            _GoBackToAtmMenuScreen();
            break;
        case enAtmOperation::eLogout:
            _Logout();
            break;
        }
    }

    static void _ShowAtmMenuScreen() {
        system("cls");
        _DrawScreenHeader("\tATM Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Transfer.\n";
        cout << setw(37) << left << "" << "\t[4] Balance.\n";
        cout << setw(37) << left << "" << "\t[5] Logout\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformAtmOperation((enAtmOperation)_ReadAtmOperation());
    }

   
    static void _GoBackToAtmMenuScreen() {
        cout << "\n\nPress any key to go back to ATM Menu Screen...";
        system("pause>0");
        _ShowAtmMenuScreen();
    }

    static short _ReadAtmOperation() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    
    

public:
    static void ShowAtmMainScreen() {

        system("cls");
        _DrawScreenHeader("\tATM Main Screen");

        string AccountNumber = _ReadAccountNumber();
        string PinCode = _ReadPinCode();

        char GoBack = 'n';
        Client = clsBankClient::Find(AccountNumber, PinCode);

        while (Client.IsEmpty()) {
            cout << "\nWrog AccountNumber, OR WrongPassword! " << endl;
            cout << "Do you want to go back? [y/n] : ";
            cin >> GoBack;
            if (GoBack == 'y' || GoBack == 'Y')
                break;

            AccountNumber = _ReadAccountNumber();
            PinCode = _ReadPinCode();
            Client = clsBankClient::Find(AccountNumber, PinCode);
        }

        if (GoBack == 'y' || GoBack == 'Y')
            _Logout();

        else {

            _ShowAtmMenuScreen();
        }
    }
};

