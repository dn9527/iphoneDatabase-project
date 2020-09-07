// main test driver for BST
// Created by Frank M. Carrano and Tim Henry.
// modified by Zhuoxuan Wang


#include "BinarySearchTree.h"  // BST ADT
#include "BinaryTree.h"
#include "iPhone.h"
#include <string>
#include <fstream>
#include <iostream>
#include "hashEntry.h"
using namespace std;

void menu(BinarySearchTree<iPhone> & iPTree1, BinarySearchTree<iPhone> & iPTree2, hashEntry &hashing);
void buildTree (const char fileName[], BinarySearchTree<iPhone> &iPTree1, BinarySearchTree<iPhone> &iPTree2, hashEntry &hashing);
int  getSize(int count);
bool isPrime(int n);
void menuMini();
void printDeveloper();
void searchByIMEI( hashEntry &hashing);


void depthTraversals(BinarySearchTree<iPhone> & iPTree);
void breadthTraversal(BinarySearchTree<iPhone> & iPTree);
void searchByCapa( BinarySearchTree<iPhone> & iPTree);
void printTreeIndented(BinarySearchTree<iPhone> & iPTree);
void printStd(iPhone &dataStd, int level);
void displayIp(iPhone &dataStd);

void deletePhone(BinarySearchTree<iPhone> & iPTree, BinarySearchTree<iPhone> &iPTree2, hashEntry &hashing);
void addPhone(BinarySearchTree<iPhone> & iPTree, BinarySearchTree<iPhone> &iPTree2, hashEntry &hashing);



int main()
{
    ifstream infile;
    char fileName[] = "iphones.txt";
    int count, size;
    infile.open(fileName);
    infile >> count; // reads the first line of the file
    
    size = getSize(count);
    hashEntry hashing(size);
    BinarySearchTree< iPhone> iPTree1;
    BinarySearchTree< iPhone> iPTree2;
    
    buildTree(fileName, iPTree1, iPTree2, hashing);
    menu(iPTree1, iPTree2, hashing);
    return 0;
}
/**~*~*
 buildSuTree function reads data from a text file
 and inserts them into a BST
 *~**/
void buildTree(const char fileName[], BinarySearchTree<iPhone> &iPTree1, BinarySearchTree<iPhone> &iPTree2, hashEntry &hashing)
{
    iPhone ip; // an iphone object
    string imei, capacity, serialNum, model, manuLocn;
    
    int count=0;
    
    ifstream infile;
    infile.open(fileName);
    cout << "Reading data from " << fileName << " . . . \n";
    if(!infile)
    {
        cout << "Error opening " << fileName << " for reading\n" ;
        exit(111);
    }
    else
    {
        infile >> count; // reads the first line of the file
        
        infile.ignore();
        while(!infile.eof())
        {
            getline(infile, imei, ' ');
            getline(infile, capacity, '\t');
            getline(infile, serialNum, '\t');
            getline(infile, model, '\t');
            getline(infile, manuLocn);
            
            ip.setInfo(imei, capacity, serialNum, model, manuLocn);
            bool inserted = iPTree1.insert(ip);
            iPTree2.insert(ip);
            iPhone* newPhone = new iPhone(imei, capacity, serialNum, model, manuLocn);
            
            hashing.insertEntry(imei, newPhone); // needed pointer because all functions in hash need ptr
            if(!inserted)
            {
                cout <<" Failed to insert. " << endl;
            }
           // else
                //cout << imei << " has been added to the list." << endl;
           //     cout << ip;
        }
    }
   
    infile.close();
    cout << "\nDone reading!\n\n";
    
    /*hashing.printEntry();
    
    cout << "Loaded factor 1: " << hashing.loadedFactor1() << '%' << endl;
    cout << "Loaded factor 2: " << hashing.loadedFactor2() << '%' <<endl;
    
    
    hashing.searchEntry("893526382134421");
    hashing.removeEntry("863356203422692");
    hashing.searchEntry("893526382134421");
    cout << endl << endl;
    
    hashing.removeEntry("645426342617182");
    hashing.printEntry();
    cout << "Loaded factor 1: " << hashing.loadedFactor1() << '%' << endl;
    cout << "Loaded factor 2: " << hashing.loadedFactor2() << '%' <<endl;
    
    */
}
//Maria
int getSize( int count)
{
    
    //given a number n, find the next closest prime number above n
        int nextPrime = 2*count;
        bool found = false;
        
        //loop continuously until isPrime returns true for a number above n
        while (!found)
        {
            nextPrime++;
            if (isPrime(nextPrime))
                found = true;
        }
        
    return nextPrime;
}

//Maria
//given a number n, determine if it is prime
    bool isPrime(int n)
    {
        //loop from 2 to n/2 to check for factors
        for (int i = 2; i <= n/2; i++)
        {
            if (n % i == 0)     //found a factor that isn't 1 or n, therefore not prime
                return false;
        }
        
        return true;
    }

/**~*~*
 printTreeIndented prints the BST as an indented list (show level numbers)
 *~**/
void printTreeIndented(BinarySearchTree<iPhone> & iPtree)
{
    //iPtree.newOrder(printStd);
}
/*******************************************************************************
 print full information of a node in the tree
 *******************************************************************************/
void printStd(iPhone &dataStd, int level)
{
    for (int i=0; i<level-1; i++)
        cout << "     ";
    cout << level << ". ";
    cout << dataStd.getIMEI() << endl;
    
}

/*******************************************************************************
 insert a newNode to tree
 *******************************************************************************/
// display function to pass to BST traverse functions
void displayIp(iPhone & ip)
{
    ip.displayInfo();
}
/**~*~*
 searchBystudentID searches by the primary key (student ID – unique key)
 *~**/
void searchByIMEI(hashEntry &hashing)
 {
     iPhone ip;
     string str = "";
 
     bool success = false;
     do
     {
         cout << "Please enter the information that you want to search:" << endl;
         cin >> str;
         if (str != "")
             success = true;
         cin.clear();          // to clear the error flag
         cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
         ip.setIMEI(str);
         hashing.searchEntry(str);
     } while (!success);
 
    
     if(!success)
         cout << "Not found!" <<endl;
 }

void searchByCapa( BinarySearchTree<iPhone> & iPTree)
 {
     iPhone ip;
     string str = "";
 
     bool success = false;
     do
     {
        cout << "Please enter the information that you want to search:" << endl;
         cin >> str;
         if (str != "")
             success = true;
         cin.clear();          // to clear the error flag
         cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
         ip.setCapacity(str);
     }
     while (!success);
 
     bool check = iPTree.getEntry(ip, ip) ;
     if(check)
         displayIp(ip);
     else
         cout << "Not found!" <<endl;
 
 }

/**~*~*
 menu function presents the user with a menu
 *~**/
void menu(BinarySearchTree<iPhone> & iPTree1, BinarySearchTree<iPhone> & iPTree2, hashEntry &hashing) // pass hash here
{
    char choice;
    iPhone ip;
    menuMini();
    do
    {
        cout<<"Enter your choice : " << endl;
        cin >> choice ;
        choice = toupper(choice);
        
        switch(choice)
        {
            case 'U':
                cout << "U - Print Unsorted List. " << endl;
                hashing.printEntry();
                break;
            case 'M':
                cout << "M - Print the List Sorted by IMEI. " << endl;
               
                break;
            case 'Y':
                cout << "Y - Print the List Sorted by Capacity. " << endl;
               
                break;
            case 'I':
                cout << "I - Search an IMEI Number. " << endl;
                searchByIMEI(hashing);
                break;
            case 'C':
                cout << "C - Search by the Capacity. " << endl;
                
                break;
            case 'A':
                cout << "A - Add a New iPhone Info. " << endl;
                addPhone(iPTree1, iPTree2, hashing);
                break;
            case 'D':
                cout << "D - Delete an iPhone Info. " << endl;
                deletePhone(iPTree1, iPTree2, hashing);
                
                break;
            case 'P':
                cout << "P – Print the iPhone Tree." << endl;
                printTreeIndented(iPTree1);
                break;
            case 'S':
            {
                cout << "S - Hash statistics." << endl;
                cout << "Loaded factor 1: " << hashing.loadedFactor1() << '%' << endl;
                cout << "Loaded factor 2: " << hashing.loadedFactor2() << '%' <<endl;
                break;
            }
            case 'R':
                cout << "R – Print the Names of the Developers." << endl;
                printDeveloper();
                break;
            case 'H':
                cout << "H – Help." << endl;
                menuMini();
                break;
            case 'E':
                cout << "E – Exit." << endl;
                hashing.writeFile();
                exit(1);
                break;
                
            default:
                cout << "Wrong choice" << endl;
        }
    } while (isalpha(choice));
}
/**~*~*
 menu function shows the menu
 *~**/
void menuMini()
{
    cout << "----------------------- Menu -----------------------\n";
    cout << "U - Print Unsorted List." << endl;
    cout << "M - Print the List Sorted by IMEI. " << endl;
    cout << "Y - Print the List Sorted by Capacity." << endl;
    cout << "I - Search an IMEI Number." << endl;
    cout << "C - Search by an Capacity." << endl;
    cout << "A - Add a New iPhone Info. " << endl;
    cout << "D - Delete an iPhone Info. " << endl;
    cout << "P – Print the iPhone Tree." << endl;
    cout << "R – Print the Names of the Developers." << endl;
    cout << "S - Hash statistics." << endl;
    cout << "H – Help (print menu)." << endl;
    cout << "E – Exit (save data to a new file)." << endl;
    cout << "----------------------------------------------------\n";
}
void deletePhone(BinarySearchTree<iPhone> & iPTree, BinarySearchTree<iPhone> &iPTree2, hashEntry &hashing)
{
    iPhone ip; // an iphone object
    string s;
    cout << "Please enter a IMEI to delete: ";
    cin >> s;
    ip.setIMEI(s);
    iPTree.getEntry(ip, ip) ;
    hashing.removeEntry(s);
    if(iPTree.remove(ip))
        cout << s << " moved successfully." << endl;
    else
        cout << "Delete fails." << endl;
    
}
void addPhone(BinarySearchTree<iPhone> & iPTree, BinarySearchTree<iPhone> &iPTree2, hashEntry &hashing)
{
    iPhone ip; // an iphone object
    iPhone *ipPtr = nullptr;
    ipPtr=&ip;
    char c;
    string imei, capacity, serialNum, model, manuLocn;
    cout << "Do you want to insert a new iPhone record(Enter Y to start): ";
    cin >> c;
    
    while(c == 'y' || c == 'Y')
    {
        cin.ignore();
        cout << "Please enter a IMEI to insert: ";
        getline(cin, imei);
        cout << "Please enter a capacity: ";
        getline(cin, capacity);
        cout << "Please enter a serial number: ";
        getline(cin, serialNum);
        cout << "Please enter a model: ";
        getline(cin, model);
        cout << "Please enter a manufacture location: ";
        getline(cin, manuLocn);
        ip.setInfo(imei, capacity, serialNum, model, manuLocn);
        iPTree.insert(ip);
        hashing.insertEntry(imei, ipPtr);
        cout << "Do you want to insert a new iPhone record(Enter Y to start): ";
        cin >> c;
        
    }
    
}
/**~*~*
 printDeveloper function shows an informaintion of the developer
 *~**/
void printDeveloper()
{
    cout << " This program is written by: " << endl;
    cout << "Maria" << endl;
    cout << "Angela" << endl;
    cout << "Mason" << endl;
    cout << "Vera" << endl;
}

/*
 DAT NGUYEN
int main()
{
    hashEntry hashing(53);
    ifstream infile("iphones.txt");
    if(!infile)
    {
        cout << "Can't open";
        exit(1);
    }

    string hold;
    getline(infile, hold);
    getline(infile, hold);
    getline(infile, hold);
    string temp1, temp2, temp3, temp4, temp5;
    while(infile)
    {
        if(infile.eof()) break;
        infile >> temp1 >> temp2 >> temp3 >> temp4 >> temp5;
        iPhone* newPhone = new iPhone(temp1, temp2, temp3, temp4, temp5);
        hashing.insertEntry(temp1, newPhone);
    }

    infile.close();

    hashing.printEntry();

    cout << "Loaded factor 1: " << hashing.loadedFactor1() << '%' << endl;
    cout << "Loaded factor 2: " << hashing.loadedFactor2() << '%' <<endl;


    hashing.searchEntry("893526382134421");
    hashing.removeEntry("863356203422692");
    hashing.searchEntry("893526382134421");
    cout << endl << endl;

    hashing.removeEntry("645426342617182");
    hashing.printEntry();
    cout << "Loaded factor 1: " << hashing.loadedFactor1() << '%' << endl;
    cout << "Loaded factor 2: " << hashing.loadedFactor2() << '%' <<endl;

}
*/
