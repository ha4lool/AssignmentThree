#include "Customer.h"

int writeCustomer(customer *cList)
{
    FILE *info;
    if ((info = fopen("info.dat", "w")))
    {
        for (int i = 0; i < 2; i++)
            if (!fwrite(cList + i, sizeof(customer), 1, info))
                return -2; //errorno changes it value based on any error so i returned a value other than 0, -1

        fclose(info);
        return 0;
    }
    return -1;
}

customer *loadCustomer(char *filename, int num)
{
    FILE *info;
    customer *cList;
    if ((info = fopen(filename, "r")))
    {
        cList = (customer *)calloc(num, sizeof(customer));
        for (int i = 0; i < num; i++)
            if (!fread(cList + i, sizeof(customer), 1, info))
                return NULL;

        fclose(info);
        return cList;
    }
    return NULL;
}

int updateCustomer(char *filename)
{
    FILE *info;
    customer cUpadated;
    if ((info = fopen(filename, "r+")))
    {
        /*
        * using ftell to get the size of the entire file 
        * then, subtract the size of one element.
        * after this we need to account for the added bytes
        * so we subtract 2 that is the last byte and the byte between
        * each element.
        */

        fseek(info, 0, SEEK_END);
        int offset = ftell(info) - sizeof(customer) - 2;

        printf("Update the Last Record");
        cUpadated = enter_customerInfo();

        fseek(info, -offset, SEEK_END);
        if (!fwrite(&cUpadated, sizeof(customer), 1, info))
            return -1;

        fclose(info);
        return 0;
    }
    return -1;
}

void print_customer(customer *c)
{
    printf("Customer's Name: %s", c->fulName);
    printf("Customer's Account#: %d\n", c->accNum);
    printf("Customer's Account Type: %s\n", c->accType);

    printf("-----------------\n");
}

customer enter_customerInfo()
{
    customer cInfo;

    /*
    * using fgets since it has bufferflow protection and reads spaces
    * i think there's an equivelant function called scanf_s that works 
    * the same way :)
    */

    printf("\nEnter Full Name: ");
    fgets(cInfo.fulName, 100, stdin);
    printf("Enter Account#: ");
    scanf("%d", &cInfo.accNum);
    getchar(); //it skips here so i added getchar()
    printf("Enter Account type (checking/saving): ");
    fgets(cInfo.accType, 15, stdin);

    return cInfo;
}