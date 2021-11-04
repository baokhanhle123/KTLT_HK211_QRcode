#include <stdio.h>
#include <string.h>

struct qrCode
{
    char dst[12];
    char stk[16];
    char owner[31];
    char bank[4];
    char create_time[9];
};

struct qrCode splitInfoQR(char *qr_mess)
{
    int qr_mess_length = strlen(qr_mess); // length of qr code
    char *ptr_i;                          //pointer "runner" ~ index

    struct qrCode qr; // struct for return
    if (strstr(qr_mess, "BKB") != NULL) // bank()stk()owner()create_time
    {
        //Get bank field
        strcpy(qr.bank, "BKB");
        printf("BKB\n");
        //Get stk field
        ptr_i = qr.stk;
        for (int i = 14; i <= 26; i++)
        {
            *ptr_i = qr_mess[i];
            ++ptr_i;
        }
        *ptr_i = '\0';

        //Get owner
        ptr_i = qr.owner;
        for (int i = 27; i <= (qr_mess_length - 9); i++)
        {
            *ptr_i = qr_mess[i];
            ++ptr_i;
        }
        *ptr_i = '\0';

        //Get create_time
        ptr_i = qr.create_time;
        for (int i = (qr_mess_length - 8); i <= (qr_mess_length - 7); i++)
        {
            *ptr_i = qr_mess[i];
            ++ptr_i;
        }
        for (int i = (qr_mess_length - 6); i <= (qr_mess_length - 5); i++)
        {
            *ptr_i = qr_mess[i];
            ++ptr_i;
        }
        for (int i = (qr_mess_length - 4); i < qr_mess_length; i++)
        {
            *ptr_i = qr_mess[i];
            ++ptr_i;
        }
        *ptr_i = '\0';
    }
    else if (strstr(qr_mess, "KHB") != NULL)
    {
        //Get bank field
        strcpy(qr.bank, "KHB");

        //Get stk field
        ptr_i = qr.stk;
        for (int i = 22; i <= 36; i++)
        {
            *ptr_i = qr_mess[i];
            ++ptr_i;
        }
        *ptr_i = '\0';

        //Get the owner field
        ptr_i = qr.owner;
        for (int i = 37; i < qr_mess_length; i++)
        {
            *ptr_i = qr_mess[i];
            ++ptr_i;
        }
        *ptr_i = '\0';

        //Get the create_time field
        ptr_i = qr.create_time;
        for (int i = 13; i <= 14; i++)
        {
            *ptr_i = qr_mess[i];
            ++ptr_i;
        }
        for (int i = 11; i <= 12; i++)
        {
            *ptr_i = qr_mess[i];
            ++ptr_i;
        }
        for (int i = 15; i <= 18; i++)
        {
            *ptr_i = qr_mess[i];
            ++ptr_i;
        }
        *ptr_i = '\0'; //null-terminated
    }
    else if (strstr(qr_mess, "HBB") != NULL)
    {
        //Get bank field
        strcpy(qr.bank, "HBB");

        //Get the stk field
        ptr_i = qr.stk;
        for (int i = (qr_mess_length - 17); i <= (qr_mess_length - 10); i++)
        {
            *ptr_i = qr_mess[i];
            ++ptr_i;
        }
        *ptr_i = '\0';

        //Get the owner field
        ptr_i = qr.owner;
        for (int i = 11; i <= (qr_mess_length - 18); i++)
        {
            *ptr_i = qr_mess[i];
            ++ptr_i;
        }
        *ptr_i = '\0';

        //Get the create_time field
        ptr_i = qr.create_time;
        for (int i = (qr_mess_length - 5); i <= (qr_mess_length - 4); i++)
        {
            *ptr_i = qr_mess[i];
            ++ptr_i;
        }
        for (int i = (qr_mess_length - 7); i <= (qr_mess_length - 6); i++)
        {
            *ptr_i = qr_mess[i];
            ++ptr_i;
        }
        //printf("/20");
        *ptr_i = '2';
        ++ptr_i;
        *ptr_i = '0';
        ++ptr_i;
        for (int i = (qr_mess_length - 9); i <= (qr_mess_length - 8); i++)
        {
            *ptr_i = qr_mess[i];
            ++ptr_i;
        }
        *ptr_i = '\0';
    }
    else
    {
        ;
    }
    return qr;
}

void printInfoQR(struct qrCode qr)
{
    printf("Ngan hang: %s\n", qr.bank);
    printf("So tai khoan: %s\n", qr.stk);
    printf("Ten chu tai khoan: %s\n", qr.owner);

    printf("Thoi diem tao QR: ");
    printf("%c%c/%c%c/", qr.create_time[0], qr.create_time[1], qr.create_time[2], qr.create_time[3]);
    char *year_field = &qr.create_time[4];
    if (strlen(year_field) == 4)
        printf("%s", year_field);
    else
        printf("20%s", year_field);
}

void checkInfoQR()
{
    /*
    Hint:
    - Look up for strstr() 
    - Look up for printf() using precision field
    */
    //Declare Menu_code and QR message
    int menu_code;
    char qr_mess[100];

    //Input QR message
    scanf("%s", qr_mess);

    //Declare qr struct
    struct qrCode qr;
    //split qr messages -> qRCode struct
    qr = splitInfoQR(qr_mess);

    //print info
    printInfoQR(qr);
}

void convertQR()
{
    /*
    Hint: 
    - Look up for strcmp(), strlen(), strcpy(), strncpy()
    */
}

void encryptQR()
{
    /*
    Hint: 
    - Look up for sprintf(), strcat(), strncat()
    */
}

int main()
{
    int menu_code;
    scanf("%d", &menu_code);
    if (menu_code == 1)
    {
        checkInfoQR();
    }
    else if (menu_code == 2)
    {
        convertQR();
    }
    else
    {
        encryptQR();
    }
    return 0;
}