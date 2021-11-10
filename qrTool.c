#include <stdio.h>
#include <string.h>

struct qrCode
{
    char dst[100];
    char stk[100];
    char owner[100];
    char bank[100];
    char create_time[100];
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

void encryptOwner(struct qrCode *qr, int encrypt_para_owner)
{
    //Not encrypt
    if (encrypt_para_owner == 0)
    {
        ;
    }
    //ASCII encrypt
    else if (encrypt_para_owner == 1)
    {
        int owner_length = 0;
        owner_length = strlen(qr->owner);
        char original_owner[100];
        strcpy(original_owner, qr->owner);
        strcpy(qr->owner, "");

        int ascii;
        char *ptr_i = &qr->owner[0];

        for (int i = 0; i < owner_length; ++i)
        {
            ascii = (int)(original_owner[i]);
            if (ascii >= 100)
            {
                *(ptr_i++) = '0' + (ascii / 100);
                *(ptr_i++) = '0' + ((ascii % 100) - (ascii % 10)) / 10;
            }
            else
                *(ptr_i++) = '0' + (ascii / 10);

            *(ptr_i++) = '0' + (ascii % 10);
            //printf("%s\n", qr->owner);
        }
        *ptr_i = '\0';

        //printf("%s\n", qr->owner);
    }
    //Index encrypt
    else if (encrypt_para_owner == 2)
    {
        int owner_length = 0;
        owner_length = strlen(qr->owner);
        char original_owner[100];
        strcpy(original_owner, qr->owner);
        strcpy(qr->owner, "");

        int encoded_num;
        char *ptr_i = &qr->owner[0];

        for (int i = 0; i < owner_length; ++i)
        {
            if (original_owner[i] >= 'A' && original_owner[i] <= 'Z')
            {
                encoded_num = original_owner[i] - 'A'; // 'C' - 'A' = 2
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
            else if (original_owner[i] >= 'a' && original_owner[i] <= 'z')
            {
                encoded_num = original_owner[i] - 'a' + 26;
                *(ptr_i++) = '0' + (encoded_num / 10);
                *(ptr_i++) = '0' + (encoded_num % 10);
            }
            //printf("%s\n", qr->owner);
        }
        *ptr_i = '\0';

        //printf("%s\n", qr->owner);
    }
    else
        ;
}

void encrypt_stk(int encrypt_para_skt)
{
    ;
}

void encrypt_qr(int encrypt_para_qr)
{
    ;
}
// Encrypt message
struct qrCode encrypt(struct qrCode qr, int encrypt_para_owner, int encrypt_para_stk, int encrypt_para_qr)
{

    struct qrCode encrypted_qr;       // struct for return
    strcpy(encrypted_qr.dst, qr.dst); // struct for return
    strcpy(encrypted_qr.stk, qr.stk);
    strcpy(encrypted_qr.owner, qr.owner);
    strcpy(encrypted_qr.bank, qr.bank);
    strcpy(encrypted_qr.create_time, qr.create_time);

    encryptOwner(&encrypted_qr, encrypt_para_owner);
    //encrypt_stk(encrypt_para_qr);
    //encrypt_qr(encrypt_para_qr);
    /*printf("#################################################\n");
    printf("%s\n", encrypted_qr.dst);
    printf("%s\n", encrypted_qr.stk);
    printf("%s\n", encrypted_qr.owner);
    printf("%s\n", encrypted_qr.bank);
    printf("%s\n", encrypted_qr.create_time);*/

    return encrypted_qr;
}

char qr_message[100] = "";
char *qr2Message(struct qrCode qr)
{
    strcpy(qr_message, "");

    if (strcmp(qr.bank, "BKB") == 0)
    {
        strcat(qr_message, qr.dst);
        strcat(qr_message, qr.bank);
        strcat(qr_message, qr.stk);
        strcat(qr_message, qr.owner);

        //Concatenate create_time
        strcat(qr_message, qr.create_time);
    }
    else if (strcmp(qr.bank, "KHB") == 0)
    {
        strcat(qr_message, qr.dst);

        //Concatenate create_time
        char *ptr_i = &qr_message[10];
        *(++ptr_i) = qr.create_time[2];
        *(++ptr_i) = qr.create_time[3]; //mm

        *(++ptr_i) = qr.create_time[0];
        *(++ptr_i) = qr.create_time[1]; //dd

        *(++ptr_i) = qr.create_time[4];
        *(++ptr_i) = qr.create_time[5];
        *(++ptr_i) = qr.create_time[6];
        *(++ptr_i) = qr.create_time[7]; //yyyy

        strcat(qr_message, qr.bank);
        strcat(qr_message, qr.stk);
        strcat(qr_message, qr.owner);
    }
    else if (strcmp(qr.bank, "HBB") == 0)
    {
        strcat(qr_message, qr.dst);
        strcat(qr_message, qr.owner);
        strcat(qr_message, qr.stk);

        //Concatenate create_time
        char *ptr_i = &qr_message[strlen(qr_message) - 1];
        *(++ptr_i) = qr.create_time[6];
        *(++ptr_i) = qr.create_time[7]; //yy

        *(++ptr_i) = qr.create_time[2];
        *(++ptr_i) = qr.create_time[3]; //mm

        *(++ptr_i) = qr.create_time[0];
        *(++ptr_i) = qr.create_time[1]; //dd

        strcat(qr_message, qr.bank);
    }
    else
    {
        strcpy(qr_message, "Ngan hang chuyen den khong hop le");
    }

    return qr_message;
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
    struct qrCode encrypted_qr = encrypt(qr, encrypt_para_owner, encrypt_para_stk, encrypt_para_qr);
    char encrypted_message[100];
    strcpy(encrypted_message, convertForm(encrypted_qr.bank, encrypted_qr));

    //Print output
    printf("%s", encrypted_message);
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