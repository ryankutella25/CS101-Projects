#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Info::Info()
{
    this->name = "No Name Set";
    this->value = "No Value Set";
    this->next = nullptr;
}

Info::Info(std::string name, std::string value, Info *next)
{
    this->name = name;
    this->value = value;
    this->next = next;
}

Contact::Contact()
{
    this->first = "No First Set";
    this->last = "No Last Set";
    this->next = nullptr;
    this->headInfoList = nullptr;
}

Contact::Contact(std::string first, std::string last, Contact *next)
{
    this->first = first;
    this->last = last;
    this->next = next;
    this->headInfoList = nullptr;
}

ContactList::ContactList()
{
    this->headContactList = nullptr;
    this->count = 0;
}

int ContactList::getCount()
{
    return this->count;
}

// print the specified contact and its information
// 1. return false and print nothing if the contact is not in the list
// 2. otherwise return true and print the contact
bool ContactList::printContact(std::ostream &os, std::string first, std::string last)
{
    if (count == 0)
    {
        return false;
    }
    else
    {
        Contact *cur = headContactList;
        while (cur != nullptr && !(cur->first == first && cur->last == last))
        {
            cur = cur->next;
        }
        if (cur == nullptr)
        {
            return false;
        }
        os << "Contact Name: " << cur->first << " " << cur->last << endl;
        Info *curInfo;
        for (curInfo = cur->headInfoList; curInfo != nullptr; curInfo = curInfo->next)
        {
            os << "   " << curInfo->name << " | " << curInfo->value << endl;
        }
        return true;
    }
}

// print all contacts and their information
// print nothing if the list is empty
void ContactList::print(std::ostream &os)
{
    if (count > 0)
    {
        Contact *cur;
        for (cur = headContactList; cur != nullptr; cur = cur->next)
        {
            os << "Contact Name: " << cur->first << " " << cur->last << endl;
            Info *curInfo;
            for (curInfo = cur->headInfoList; curInfo != nullptr; curInfo = curInfo->next)
            {
                os << "/t" << curInfo->name << " | " << curInfo->value << endl;
            }
        }
    }
}

// add a contact to the back of the list
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the back of the list
// - do not forget to update count
bool ContactList::addContact(std::string first, std::string last)
{
    // if list is empty
    if (count == 0)
    {
        headContactList = new Contact(first, last, nullptr);
        count++;
        return true;
    }
    // if list has items
    Contact *cur = headContactList;
    // if its first
    if (cur->first == first && cur->last == last)
    {
        return false;
    }
    // traverse to last contact
    // while returning false if we find the contact
    while (cur->next != nullptr)
    {
        if (cur->next->first == first && cur->next->last == last)
        {
            return false;
        }
        cur = cur->next;
    }
    cur->next = new Contact(first, last, nullptr);
    count++;
    return true;
}

// add info to the back of a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the back of the contact's list and return true
bool ContactList::addInfo(std::string first, std::string last, std::string infoName, std::string infoVal)
{
    Contact *cur = headContactList;
    // traverse to end until we find it
    while (cur != nullptr && !(cur->first == first && cur->last == last))
    {
        cur = cur->next;
    }
    if (cur == nullptr)
    {
        return false;
    }
    // if empty
    if (cur->headInfoList == nullptr)
    {
        cur->headInfoList = new Info(infoName, infoVal, nullptr);
        return true;
    }
    // if list has items
    Info *curInfo = cur->headInfoList;
    // if its first
    if (curInfo->name == infoName)
    {
        curInfo->value = infoVal;
        return true;
    }
    // traverse to last contact
    // while returning false if we find the contact
    while (curInfo->next != nullptr)
    {
        if (curInfo->next->name == infoName)
        {
            curInfo->next->value = infoVal;
            return true;
        }
        curInfo = curInfo->next;
    }
    curInfo->next = new Info(infoName, infoVal, nullptr);
    return true;
}

// return -1 if contact is less than last, first
// return 0 if contact is same as last, first
// return 1 if contact is greater than last, first
int compareContact(Contact *cur, std::string first, std::string last)
{
    if (cur->last == last)
    {
        if (cur->first == first)
        {
            return 0;
        }
        else
        {
            if (cur->first > first)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
    }
    else if (cur->last > last)
    {
        return 1;
    }
    // less than
    else
    {
        return -1;
    }
}

// return -1 if info is less than last, first
// return 0 if info is same as last, first
// return 1 if info is greater than last, first
int compareInfo(Info *cur, std::string infoName)
{
    if (cur->name == infoName)
    {
        return 0;
    }
    else if (cur->name > infoName)
    {
        return 1;
    }
    // less than
    else
    {
        return -1;
    }
}

// add a contact to the list in ascending order by last name
//     if last names are equal, then order by first name ascending
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the list
// - do not forget to update count
// - compare strings with the built-in comparison operators: <, >, ==, etc.
// - a compare method/function is recommended
bool ContactList::addContactOrdered(std::string first, std::string last)
{
    // if list is empty
    if (count == 0)
    {
        headContactList = new Contact(first, last, nullptr);
        count++;
        return true;
    }
    // if list has items
    Contact *cur = headContactList;
    // compare to first
    int comp = compareContact(cur, first, last);
    // equal to
    if (comp == 0)
    {
        return false;
    }
    // contact is greater than below
    else if (comp == 1)
    {
        Contact *temp = new Contact(first, last, headContactList);
        headContactList = temp;
        count++;
        return true;
    }
    // p p p p p p p pp p p p
    //  traverse to until the contact is greater than
    if (cur->next != nullptr)
    {
        comp = compareContact(cur->next, first, last);
        while (comp < 0)
        {
            cur = cur->next;
            if (cur->next == nullptr)
            {
                break;
            }
            comp = compareContact(cur->next, first, last);
        }
    }
    // reached end
    if (cur->next == nullptr)
    {
        cur->next = new Contact(first, last, nullptr);
        count++;
        return true;
    }
    // comp was equal so it found it
    if (comp == 0)
    {
        return false;
    }
    // comp is greater than and didnt reach the end so input
    // after cur
    Contact *temp = new Contact(first, last, cur->next);
    cur->next = temp;
    count++;
    return true;
}

// add info to a contact's info list in ascending order by infoName
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the contact's list and return true
bool ContactList::addInfoOrdered(std::string first, std::string last, std::string infoName, std::string infoVal)
{
    Contact *cur = headContactList;
    // traverse to end until we find it
    while (cur != nullptr && !(cur->first == first && cur->last == last))
    {
        cur = cur->next;
    }
    if (cur == nullptr)
    {
        return false;
    }
    // if empty
    if (cur->headInfoList == nullptr)
    {
        cur->headInfoList = new Info(infoName, infoVal, nullptr);
        return true;
    }
    // if list has items
    Info *curInfo = cur->headInfoList;
    // compare to first
    int comp = compareInfo(curInfo, infoName);
    // equal to
    if (comp == 0)
    {
        curInfo->value = infoVal;
        return true;
    }
    // contact is greater than below
    else if (comp == 1)
    {
        cur->headInfoList = new Info(infoName, infoVal, cur->headInfoList);
        return true;
    }
    // p p p p p p p pp p p p
    //  traverse to until the info is greater than
    if (curInfo->next != nullptr)
    {
        comp = compareInfo(curInfo->next, infoName);
        while (comp < 0)
        {
            curInfo = curInfo->next;
            if (curInfo->next == nullptr)
            {
                break;
            }
            comp = compareInfo(curInfo->next, infoName);
        }
    }
    // reached end
    if (curInfo->next == nullptr)
    {
        curInfo->next = new Info(infoName, infoVal, nullptr);
        return true;
    }
    // comp was equal so it found it
    if (comp == 0)
    {
        curInfo->next->value = infoVal;
        return true;
    }
    // comp is greater than and didnt reach the end so input
    // after cur
    curInfo->next = new Info(infoName, infoVal, curInfo->next);
    return true;
}

// remove the contact and its info from the list
// 1. return false and do nothing if the contact is not in the list
// 2. otherwise return true and remove the contact and its info
// - do not forget to update count
// MIGHT NOT BE DONE
bool ContactList::removeContact(std::string first, std::string last)
{
    // empty array return false
    if (count == 0)
    {
        return false;
    }
    else
    {
        Contact *cur = headContactList;
        Info *curInfo;
        // contact is first
        if (compareContact(cur, first, last) == 0)
        {
            curInfo = cur->headInfoList;
            Contact *oldContact = headContactList;
            headContactList = oldContact->next;
            delete oldContact;
            count--;
        }
        else
        {
            // gets cur to be right before spot or to nullptr
            while (cur->next != nullptr && compareContact(cur->next, first, last) != 0)
            {
                cur = cur->next;
            }
            // if contact doesnt exist
            if (cur->next == nullptr)
            {
                return false;
            }
            // else set curInfo and delete contact
            else
            {
                curInfo = cur->next->headInfoList;
                Contact *oldContact = cur->next;
                cur->next = oldContact->next;
                delete oldContact;
                count--;
            }
        }
        // Contact is deleted now and curInfo is set
        if (curInfo == nullptr)
        {
            return true;
        }
        while (curInfo != nullptr)
        {
            Info *temp = curInfo;
            curInfo = curInfo->next;
            delete temp;
        }
        return true;
    }
}

// remove the info from a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. return false and do nothing if the info is not in the contact's info list
// 3. otherwise return true and remove the info from the contact's list
// MIGHT NOT BE DONE
bool ContactList::removeInfo(std::string first, std::string last, std::string infoName)
{
    // empty array return false
    if (count == 0)
    {
        return false;
    }
    else
    {
        Contact *cur = headContactList;
        Info *curInfo;
        // gets cur to be spot or nullptr
        while (cur != nullptr && compareContact(cur, first, last) != 0)
        {
            cur = cur->next;
        }
        // if contact doesnt exist
        if (cur == nullptr)
        {
            return false;
        }
        // else set curInfo
        else
        {
            curInfo = cur->headInfoList;
        }
        // curInfo is set past this point

        // this is for when the infolist is empty
        if (curInfo == nullptr)
        {
            return false;
        }

        // when its first in list
        if (curInfo->name == infoName)
        {
            Info *oldHead = curInfo;
            cur->headInfoList = oldHead->next;
            delete oldHead;
            return true;
        }
        // gets curInfo to nullptr or right before
        while (curInfo->next != nullptr && curInfo->next->name != infoName)
        {
            curInfo = curInfo->next;
        }
        // went through list and not found
        if (curInfo->next == nullptr)
        {
            return false;
        }
        Info *oldInfo = curInfo->next;
        curInfo->next = oldInfo->next;
        delete oldInfo;
        return true;
    }
}

// destroy the list by removing all contacts and their infos
// MIGHT NOT BE DONE
ContactList::~ContactList()
{
    if (count != 0)
    {
        Contact *currentContact = this->headContactList;
        while (currentContact != nullptr)
        {
            Contact *temp = currentContact;
            currentContact = temp->next;
            Info *currentInfo = temp->headInfoList;
            delete temp;
            while (currentInfo != nullptr)
            {
                Info *tempInfo = currentInfo;
                currentInfo = tempInfo->next;
                delete tempInfo;
            }
            // dont need to delete currentInfo because will both be nullptr;
        }
        // dont need to delete currentContact since its nullptr
        count = 0;
    }
}

// deep copy the source list
// - do not forget to update count
// MIGHT NOT BE DONE
ContactList::ContactList(const ContactList &src)
{
    headContactList = nullptr;
    count = 0;
    Contact *currentContact = src.headContactList;
    while (currentContact != nullptr)
    {
        this->addContact(currentContact->first, currentContact->last);
        count++;
        Info *currentInfo = currentContact->headInfoList;
        while (currentInfo != nullptr)
        {
            this->addInfo(currentContact->first, currentContact->last, currentInfo->name, currentInfo->value);
            currentInfo = currentInfo->next;
        }
        currentContact = currentContact->next;
    }
}

// remove all contacts and their info then deep copy the source list
// - do not forget to update count
// MIGHT NOT BE DONE
const ContactList &ContactList::operator=(const ContactList &src)
{
    if (this != &src)
    {
        if (count != 0)
        {
            Contact *currentContact = this->headContactList;
            headContactList = nullptr;
            while (currentContact != nullptr)
            {
                Contact *temp = currentContact;
                currentContact = temp->next;
                Info *currentInfo = temp->headInfoList;
                delete temp;
                while (currentInfo != nullptr)
                {
                    Info *tempInfo = currentInfo;
                    currentInfo = tempInfo->next;
                    delete tempInfo;
                }
                // dont need to delete currentInfo because will both be nullptr;
            }
            // dont need to delete currentContact since its nullptr
            count = 0;
        }
        // now its a basic ContactList
        Contact *currentContact = src.headContactList;
        while (currentContact != nullptr)
        {
            this->addContact(currentContact->first, currentContact->last);
            Info *currentInfo = currentContact->headInfoList;
            while (currentInfo != nullptr)
            {
                this->addInfo(currentContact->first, currentContact->last, currentInfo->name, currentInfo->value);
                currentInfo = currentInfo->next;
            }
            currentContact = currentContact->next;
        }
    }
    return *this;
}
