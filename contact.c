#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

void listContacts(AddressBook *addressBook)
{    
   if(addressBook->contactCount == 0)
    {
        printf(CYAN"No contacts found\n"RESET);
        return;
    }
     for(int i = 0; i < addressBook->contactCount - 1; i++)
{
    for(int j = i + 1; j < addressBook->contactCount; j++)
    {
        if(strcmp(addressBook->contacts[i].name,
                  addressBook->contacts[j].name) > 0)
        {
            Contact temp;

            temp = addressBook->contacts[i];
            addressBook->contacts[i] = addressBook->contacts[j];
            addressBook->contacts[j] = temp;
        }
    }
}
     
    printf(YELLOW"\n----------------------Contact List-----------------------------"RESET);
    printf(MAGENTA"\n---------------------------------------------------------------\n"RESET);
    printf(YELLOW"%-7s %-15s %-15s %-30s\n",
           "Sr.No", "Name", "Phone", "Email"RESET);
    printf(MAGENTA"---------------------------------------------------------------\n"RESET);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-7d %-15s %-15s %-30s\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf(MAGENTA"---------------------------------------------------------------\n"RESET);
    printf(CYAN"Total Contacts: %d\n"RESET, addressBook->contactCount); 
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
int validate_name(char *str)
{
    int i = 0;

    while (str[i])
    {
   
        if ((str[i] >= 'a' && str[i] <= 'z') ||(str[i] >= 'A' && str[i] <= 'Z') || str[i] == '.' ||str[i] == ' ')
	{
		i++;
	}
	else
	{
		return 0;
	}	
    }
      return 1;
}
int validate_phone(char *str)
{
    int i = 0;

    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }

    if (i != 10)
        return 0;

    return 1;
}

int validate_mail(char *str)
{
    int i = 0, count = 0;

    if (!(str[0] >= 'a' && str[0] <= 'z'))
        return 0;

    while (str[i])
    {
        if ((str[i] >= 'a' && str[i] <= 'z') ||
            (str[i] >= '0' && str[i] <= '9') ||
            str[i] == '@' || str[i] == '.')
        {
            if (str[i] == '@')
                count++;
        }
        else
            return 0;

        i++;
    }

    if (count != 1 || i < 5 ||
        str[i-4] != '.' || str[i-3] != 'c' ||
        str[i-2] != 'o' || str[i-1] != 'm')
        return 0;

    return 1;
}
        

void createContact(AddressBook *addressBook)
{
   if(addressBook->contactCount >= MAX_CONTACTS)
   {
        printf(CYAN"Address book is full\n"RESET);
        return;
   }
	int res;
	char name[20];
	do
	{
		printf("Enter the name:");
		scanf(" %19[^\n]", name);
		res=validate_name(name);
		if(res==0)
			printf(RED"Invalid Name\n"RESET);
	}while(res==0);

	char phone[11];
        do
        {
                printf("Enter the phone_no:");
                scanf("%s",phone);
                res=validate_phone(phone);
		if(res==0)
		{
			printf(RED"Invalid Phone Number\n"RESET);
			continue;
		}
	   for (int i = 0; i < addressBook->contactCount; i++)
           {
              if (strcmp(phone, addressBook->contacts[i].phone) == 0)
              {
                printf(BLUE"Phone number already exists\n"RESET);
                res = 0;
                break;
              }
           }

        }while(res==0);

	char mail[20];
        do
        {
                printf("Enter the mail:");
                scanf("%s",mail);
                res=validate_mail(mail);
		if(res==0)
		{
			printf(RED"Invalid Mail\n"RESET);
			continue;
		}
          for (int i = 0; i < addressBook->contactCount; i++)
          {
              if (strcmp(mail, addressBook->contacts[i].email) == 0)
              {
                printf(BLUE"Mail already exists\n"RESET);
                res = 0;
                break;
              }
          }
        }while(res==0);

	strcpy(addressBook->contacts[addressBook->contactCount].name, name);
strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
strcpy(addressBook->contacts[addressBook->contactCount].email, mail);

addressBook->contactCount++;
printf(GREEN"Contact created successfully\n"RESET);
	
 }
 
int searchContact(AddressBook *addressBook)
{
    int choice, count = 0, index = -1;
    char search[50], phone[20];

    printf("1. Search by name\n");
    printf("2. Search by phone\n");
    printf("3. Search by email\n");
    printf("Enter choice: ");
    if(scanf("%d", &choice)!=1)
    {
	    printf(RED"Invalid Choice\n"RESET);
	    while(getchar()!='\n');
	    return -1;
    }

    switch(choice)
    {
        case 1:
            printf("Enter name: ");
            scanf(" %[^\n]", search);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(search, addressBook->contacts[i].name) == 0)
                {
	            printf(GREEN"Contact Found:\n"RESET);
                    printf("\nName  : %s\n", addressBook->contacts[i].name);
                    printf("Phone : %s\n", addressBook->contacts[i].phone);
                    printf("Email : %s\n", addressBook->contacts[i].email);

                    index = i;
                    count++;
                }
            }

            if(count == 0)
            {
                printf(BLUE"Contact not found\n"RESET);
                return -1;
            }

            if(count > 1)
            {
                printf("Enter phone number: ");
                scanf("%s", phone);

                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcmp(search, addressBook->contacts[i].name) == 0 &&
                       strcmp(phone, addressBook->contacts[i].phone) == 0)
                    {    
                     	printf(GREEN"Contact Found:\n"RESET);
                        printf("Name  : %s\n", addressBook->contacts[i].name);
                        printf("Phone : %s\n", addressBook->contacts[i].phone);
                        printf("Email : %s\n", addressBook->contacts[i].email);
                        return i;
                    }
                }

                printf(BLUE"Contact not found\n"RESET);
                return -1;
            }

            return index;

        case 2:
            printf("Enter phone number: ");
            scanf("%s", search);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(search, addressBook->contacts[i].phone) == 0)
                {
		    printf(GREEN"Contact Found:"RESET);
                    printf("\nName  : %s\n", addressBook->contacts[i].name);
                    printf("Phone : %s\n", addressBook->contacts[i].phone);
                    printf("Email : %s\n", addressBook->contacts[i].email);

                    return i;
                }
            }

            printf(BLUE"Contact not found\n"RESET);
            return -1;

        case 3:
            printf("Enter email: ");
            scanf("%s", search);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(search, addressBook->contacts[i].email) == 0)
                {
		    printf(GREEN"Contact Found:"RESET);
                    printf("\nName  : %s\n", addressBook->contacts[i].name);
                    printf("Phone : %s\n", addressBook->contacts[i].phone);
                    printf("Email : %s\n", addressBook->contacts[i].email);

                    return i;
                }
            }

            printf(BLUE"Contact not found\n"RESET);
            return -1;

        default:
            printf(RED"Invalid choice\n"RESET);
            return -1;
    }
}


void editContact(AddressBook *addressBook)
{
    int index, choice, res;
    char name[50], phone[20], email[50];

    index = searchContact(addressBook);

    if (index == -1)
        return;

    printf("\n1. Edit Name\n");
    printf("2. Edit Phone\n");
    printf("3. Edit Email\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            do
            {
                printf("Enter new name: ");
                scanf(" %[^\n]", name);

                res = validate_name(name);

                if(res == 0)
                    printf(RED"Invalid Name\n"RESET);

            } while(res == 0);

            strcpy(addressBook->contacts[index].name, name);
            break;

        case 2:
            do
            {
                printf("Enter new phone: ");
                scanf("%s", phone);

                res = validate_phone(phone);

                if(res == 0)
                    printf(RED"Invalid Phone Number\n"RESET);

            } while(res == 0);

            /* Check duplicate phone */
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(i != index && strcmp(phone, addressBook->contacts[i].phone) == 0)
	        {
                    printf(BLUE"Phone number already exists\n"RESET);
                    return;
                }
            }

            strcpy(addressBook->contacts[index].phone, phone);
            break;

        case 3:
            do
            {
                printf("Enter new email: ");
                scanf("%s", email);

                res = validate_mail(email);

                if(res == 0)
                    printf(RED"Invalid Mail\n"RESET);

            } while(res == 0);

            /* Check duplicate email */
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(i != index &&
                   strcmp(email, addressBook->contacts[i].email) == 0)
                {
                    printf(BLUE"Mail already exists\n"RESET);
                    return;
                }
            }

            strcpy(addressBook->contacts[index].email, email);
            break;

        default:
            printf(RED"Invalid choice\n"RESET);
            return;
    }

    printf(GREEN"Contact updated successfully\n"RESET);

    
}

void deleteContact(AddressBook *addressBook)
{
    int index;

    index = searchContact(addressBook);

    if(index == -1)
        return;
char choice;

printf(YELLOW"Are you sure you want to delete this contact? (y/n): "RESET);
scanf(" %c", &choice);

if(choice != 'y' && choice != 'Y')
{
    printf(RED"Delete cancelled\n"RESET);
    return;
}

    for(int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf(GREEN"Contact deleted successfully\n"RESET);

   

}
