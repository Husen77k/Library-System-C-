#include <iostream>
#include <string>
using namespace std;

class LibraryItem
{
private:
    string title;
    string author;
    string dueDate;

public:
    LibraryItem(string t, string a)
    {
        title = t;
        author = a;
        dueDate = "";
    }

    string getTitle()
    {
        return title;
    }

    string getAuthor()
    {
        return author;
    }

    string getDueDate()
    {
        return dueDate;
    }

    void setTitle(string newTitle)
    {
        title = newTitle;
    }

    void setAuthor(string newAuthor)
    {
        author = newAuthor;
    }

    void setDueDate(string newDueDate)
    {
        dueDate = newDueDate;
    }

    virtual void checkOut() = 0;
    virtual void returnItem() = 0;
    virtual void displayDetails() = 0;

    virtual ~LibraryItem() {}
};

class Book : public LibraryItem
{
private:
    int pages;

public:
    Book(string title, string author, int p)
        : LibraryItem(title, author)
    {
        pages = p;
    }

    void checkOut() override
    {
        setDueDate("30-09-2026");
        cout << "Book checked out successfully.\n";
    }

    void returnItem() override
    {
        setDueDate("");
        cout << "Book returned successfully.\n";
    }

    void displayDetails() override
    {
        cout << "\nType: Book";
        cout << "\nTitle: " << getTitle();
        cout << "\nAuthor: " << getAuthor();
        cout << "\nPages: " << pages;
        cout << "\nDue Date: " << (getDueDate() == "" ? "Not issued" : getDueDate()) << endl;
    }
};

class DVD : public LibraryItem
{
private:
    int duration;

public:
    DVD(string title, string author, int d)
        : LibraryItem(title, author)
    {
        duration = d;
    }

    void checkOut() override
    {
        setDueDate("30-09-2026");
        cout << "DVD checked out successfully.\n";
    }

    void returnItem() override
    {
        setDueDate("");
        cout << "DVD returned successfully.\n";
    }

    void displayDetails() override
    {
        cout << "\nType: DVD";
        cout << "\nTitle: " << getTitle();
        cout << "\nAuthor: " << getAuthor();
        cout << "\nDuration: " << duration << " minutes";
        cout << "\nDue Date: " << (getDueDate() == "" ? "Not issued" : getDueDate()) << endl;
    }
};

class Magazine : public LibraryItem
{
private:
    int issueNumber;

public:
    Magazine(string title, string author, int issue)
        : LibraryItem(title, author)
    {
        issueNumber = issue;
    }

    void checkOut() override
    {
        setDueDate("30-09-2026");
        cout << "Magazine checked out successfully.\n";
    }

    void returnItem() override
    {
        setDueDate("");
        cout << "Magazine returned successfully.\n";
    }

    void displayDetails() override
    {
        cout << "\nType: Magazine";
        cout << "\nTitle: " << getTitle();
        cout << "\nAuthor: " << getAuthor();
        cout << "\nIssue Number: " << issueNumber;
        cout << "\nDue Date: " << (getDueDate() == "" ? "Not issued" : getDueDate()) << endl;
    }
};

int main()
{
    const int MAX_ITEMS = 10;
    LibraryItem* libraryItems[MAX_ITEMS];
    int count = 0;
    int choice;

    do
    {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Add DVD\n";
        cout << "3. Add Magazine\n";
        cout << "4. Display Items\n";
        cout << "5. Check Out Item\n";
        cout << "6. Return Item\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";

        try
        {
            cin >> choice;

            if (cin.fail())
            {
                throw invalid_argument("Invalid input");
            }

            if (choice == 1)
            {
                if (count >= MAX_ITEMS)
                    throw runtime_error("Library is full.");

                string title, author;
                int pages;

                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);

                cout << "Enter author: ";
                getline(cin, author);

                cout << "Enter pages: ";
                cin >> pages;

                if (pages <= 0)
                    throw invalid_argument("Pages must be greater than 0.");

                libraryItems[count] = new Book(title, author, pages);
                count++;

                cout << "Book added successfully.\n";
            }
            else if (choice == 2)
            {
                if (count >= MAX_ITEMS)
                    throw runtime_error("Library is full.");

                string title, author;
                int duration;

                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);

                cout << "Enter author: ";
                getline(cin, author);

                cout << "Enter duration: ";
                cin >> duration;

                if (duration <= 0)
                    throw invalid_argument("Duration must be greater than 0.");

                libraryItems[count] = new DVD(title, author, duration);
                count++;

                cout << "DVD added successfully.\n";
            }
            else if (choice == 3)
            {
                if (count >= MAX_ITEMS)
                    throw runtime_error("Library is full.");

                string title, author;
                int issue;

                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);

                cout << "Enter author: ";
                getline(cin, author);

                cout << "Enter issue number: ";
                cin >> issue;

                if (issue <= 0)
                    throw invalid_argument("Issue number must be greater than 0.");

                libraryItems[count] = new Magazine(title, author, issue);
                count++;

                cout << "Magazine added successfully.\n";
            }
            else if (choice == 4)
            {
                if (count == 0)
                {
                    cout << "No items available.\n";
                }
                else
                {
                    for (int i = 0; i < count; i++)
                    {
                        cout << "\nItem " << i + 1;
                        libraryItems[i]->displayDetails();
                    }
                }
            }
            else if (choice == 5)
            {
                int number;

                cout << "Enter item number: ";
                cin >> number;

                if (number < 1 || number > count)
                    throw out_of_range("Invalid item number.");

                libraryItems[number - 1]->checkOut();
            }
            else if (choice == 6)
            {
                int number;

                cout << "Enter item number: ";
                cin >> number;

                if (number < 1 || number > count)
                    throw out_of_range("Invalid item number.");

                libraryItems[number - 1]->returnItem();
            }
            else if (choice == 7)
            {
                cout << "Program ended.\n";
            }
            else
            {
                throw invalid_argument("Invalid choice.");
            }
        }
        catch (exception &e)
        {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }

    } while (choice != 7);

    for (int i = 0; i < count; i++)
    {
        delete libraryItems[i];
    }

    return 0;
}