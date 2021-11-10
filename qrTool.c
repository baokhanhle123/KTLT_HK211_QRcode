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
    strcpy(qr.dst, "00020101021");

    if (strstr(qr_mess, "BKB") != NULL) // bank()stk()owner()create_time
    {
        //Get bank field
        strcpy(qr.bank, "BKB");
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

//Declare return form
char newForm[100] = "";

char *convertForm(char *dest_bank, struct qrCode qr)
{
    if (strcmp(dest_bank, "BKB") == 0)
    {
        strcat(newForm, qr.dst);
        strcat(newForm, qr.bank);
        strcat(newForm, qr.stk);
        strcat(newForm, qr.owner);

        //Concatenate create_time
        strcat(newForm, qr.create_time);
    }
    else if (strcmp(dest_bank, "KHB") == 0)
    {
        strcat(newForm, qr.dst);

        //Concatenate create_time
        char *ptr_i = &newForm[10];
        *(++ptr_i) = qr.create_time[2];
        *(++ptr_i) = qr.create_time[3]; //mm

        *(++ptr_i) = qr.create_time[0];
        *(++ptr_i) = qr.create_time[1]; //dd

        *(++ptr_i) = qr.create_time[4];
        *(++ptr_i) = qr.create_time[5];
        *(++ptr_i) = qr.create_time[6];
        *(++ptr_i) = qr.create_time[7]; //yyyy

        strcat(newForm, qr.bank);
        strcat(newForm, qr.stk);
        strcat(newForm, qr.owner);
    }
    else if (strcmp(dest_bank, "HBB") == 0)
    {
        strcat(newForm, qr.dst);
        strcat(newForm, qr.owner);
        strcat(newForm, qr.stk);

        //Concatenate create_time
        char *ptr_i = &newForm[strlen(newForm) - 1];
        *(++ptr_i) = qr.create_time[6];
        *(++ptr_i) = qr.create_time[7]; //yy

        *(++ptr_i) = qr.create_time[2];
        *(++ptr_i) = qr.create_time[3]; //mm

        *(++ptr_i) = qr.create_time[0];
        *(++ptr_i) = qr.create_time[1]; //dd

        strcat(newForm, qr.bank);
    }
    else
    {
        strcpy(newForm, "Ngan hang chuyen den khong hop le");
    }

    return newForm;
}

void convertQR()
{
    /*
    Hint: 
    - Look up for strcmp(), strlen(), strcpy(), strncpy()
    */
    //Declare QR message
    char qr_mess[100];

    //Input destination bank:
    char dest_bank[4];
    scanf("%s", dest_bank);

    //Input QR message
    scanf("%s", qr_mess);

    //Declare qr struct
    struct qrCode qr;
    //split qr messages -> qRCode struct
    qr = splitInfoQR(qr_mess);

    //Convert form
    char newForm[100];
    strcpy(newForm, convertForm(dest_bank, qr));

    //Print output
    printf("%s", newForm);
}

void encrypt_owner(char *owner, int encrypt_para_owner)
{
    //Not encrypt
    if (encrypt_para_owner == 0)
        ;
    else if (encrypt_para_owner == 1)
    {
        int owner_length = 0;
        owner_length = strlen(owner);

        char encoded_owner[100] = "";

        int ascii;
        char *ptr_i = &encoded_owner[strlen(encoded_owner)];

        for (int i = 0; i < owner_length; ++i)
        {
            ascii = (int)(owner[i]);
            ptr_i = &encoded_owner[strlen(encoded_owner)];
            if (ascii >= 100)
            {
                *(ptr_i++) = '0' + (ascii / 100);
                *(ptr_i++) = '0' + ((ascii % 100) - (ascii % 10)) / 10;
            }
            else
                *(ptr_i++) = '0' + (ascii / 10);
            *(ptr_i++) = '0' + (ascii % 10);
        }
        strcpy(owner, encoded_owner);
    }
    else if (encrypt_para_owner == 2)
    {
        int owner_length = 0;
        owner_length = strlen(owner);

        char encoded_owner[100] = "";

        int ascii;
        int encoded_num;
        char *ptr_i = &encoded_owner[strlen(encoded_owner)];

        for (int i = 0; i < owner_length; ++i)
        {
            ascii = (int)(owner[i]);
            ptr_i = &encoded_owner[strlen(encoded_owner)];
            if (ascii >= 65 && ascii <= 90)
            {
                encoded_num = owner[i] - 'A'; // 'C' - 'A' = 2
                if (encoded_num < 10)
                {
                    *(ptr_i++) = '0';
                    *(ptr_i++) = '0' + (encoded_num);
                }
                else
                {
                    *(ptr_i++) = '0' + (encoded_num / 10);
                    *(ptr_i++) = '0' + (encoded_num % 10);
                }
            }
            else if (ascii >= 97 && ascii <= 122)
            {
                encoded_num = owner[i] - 'a' + 26;
                *(ptr_i++) = '0' + (encoded_num / 10);
                *(ptr_i++) = '0' + (encoded_num % 10);
            }
        }
        printf("\n");
        strcpy(owner, encoded_owner);
    }
    else
        return;
}

void encrypt_stk(int encrypt_para_skt)
{
    ;
}

void encrypt_qr(int encrypt_para_qr)
{
    ;
}

char returnEncrypt[100] = "";
// Encrypt message
char *encrypt(struct qrCode *qr, int encrypt_para_owner, int encrypt_para_stk, int encrypt_para_qr)
{
    encrypt_owner(qr->owner, encrypt_para_owner);
    encrypt_stk(encrypt_para_qr);
    encrypt_qr(encrypt_para_qr);

    //return encrypt message
    strcat(returnEncrypt, qr->dst);
    strcat(returnEncrypt, qr->bank);
    strcat(returnEncrypt, qr->stk);
    strcat(returnEncrypt, qr->owner);
    strcat(returnEncrypt, qr->create_time);

    return returnEncrypt;
}

void encryptQR()
{
    /*
    Hint: 
    - Look up for sprintf(), strcat(), strncat()
    */
    //Input encrypt_parameter
    int encrypt_para_owner = 0;
    int encrypt_para_stk = 0;
    int encrypt_para_qr = 0;
    scanf("%d%d%d", &encrypt_para_owner, &encrypt_para_stk, &encrypt_para_qr);

    //Input QR message
    char qr_mess[100];
    scanf("%s", qr_mess);
    //Declare qr struct
    struct qrCode qr;
    //split qr messages -> qRCode struct
    qr = splitInfoQR(qr_mess);

    //Encrypting ...
    char encoded_qr[100];
    strcpy(encoded_qr, encrypt(&qr, encrypt_para_owner, encrypt_para_stk, encrypt_para_qr));

    //Print output
    printf("%s", encoded_qr);
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
    /*char tenchuTKMaHoa[100] = ""; 

    int ascii = (int)'A';
    char *ptr_i = &tenchuTKMaHoa[strlen(tenchuTKMaHoa)];
    *(ptr_i++) = '0' + (ascii / 10);
    *(ptr_i++) = '0' + (ascii % 10);
    printf("%s\n", tenchuTKMaHoa);*/
}