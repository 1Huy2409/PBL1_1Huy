#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define N 100
typedef struct
{
    int ngay, thang, nam;
} date;
typedef struct
{
    char home[5], street[30], city[30];
} address;
typedef struct
{
    char middle[30], name[30], sex[10];
    int age;
    date birth;
    address OfSv;
} sinhvien;
typedef struct
{
    long long id;
    char email[30];
} idmail;
// khai bao 2 mang song song: 1 mang luu thong tin cb cua sinh vien con 1 mang de luu ma sinh vien va email cua sinh vien
sinhvien list[N]; // mang co ten la list kieu struct sinhvien
idmail ID[N];     // mang co ten la ID kieu struct là idmail
int check = 0;    // dung de check xem danh sach sinh vien da duoc sap xep hay chua
int chooseMenu;   // lua chon trong menu chinh cua chuong trinh
int sumSv, count = 0, res = 0;
long long delSv;       // so luong sinh vien da bi xoa ra khoi danh sach
int idSv;              // id cua sinh vien can xoa
char fileName[100];    // ten file txt dua tu ngoai vao code
char confirmDelAll[2]; // xac nhan chac chan xoa
int sv;                // id cua sinh vien can tim

void addSv(sinhvien *sv);
void sortSv(sinhvien list[], int l, int r);                   
void deleteMsv(sinhvien list[], idmail ID[], int *n, int sv); 
void deleteAll(char fileName[]);
int binarySearchName(sinhvien list[], idmail msv[], int left, int right, char Name[]);
int binarySearchMsv(idmail msv[], int left, int right, long long idsv);
void initId();
void initEmail();
void scanlist();
int test(char fileName[]);
void menu();
void Intro();
int main()
{
    Intro();
    menu();
}
int test(char fileName[])
{ // truyen ten ham
    time_t rawtime;
    struct tm *timeinfo;
    int year;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    year = timeinfo->tm_year + 1900;
    char nam[10];
    sprintf(nam, "%d", year);
    char chuoi1[3]; // lay nien khoa cua nam hoc sinh vien
    int i;
    for (i = 0; i < 2; i++)
    {
        chuoi1[i] = fileName[i];
    } // nien khoa lay 2 ky tu dau cua chuoi me
    chuoi1[i] = '\0';
    char cnam[3];
    int j, k = 0;
    for (j = 2; j <= 3; j++)
    {
        cnam[k++] = nam[j];
    }
    cnam[k] = '\0';
    if (strcmp(cnam, chuoi1) == 0)
    {
        return 1;
    }
    else
        return 0;
}
// ham uppercase
char to_upper(char s)
{
    if (s >= 'a' && s <= 'z')
    {
        s -= 32;
    }
}
// ham lowercase
char to_lower(char s)
{
    if (s >= 'A' && s <= 'Z')
    {
        s += 32;
    }
}
// ham chuan hoa chuoi nhap vao tu input
void standard(char s[])
{
    while (s[0] == ' ')
    {
        strcpy(&s[0], &s[1]);
    }
    s[0] = to_upper(s[0]);
    int i;
    for (i = 0; i < strlen(s) - 1; i++)
    {
        if (s[i] == ' ' && s[i + 1] == ' ')
        {
            strcpy(&s[i], &s[i + 1]);
            i--;
        }
    }
    while (s[strlen(s) - 2] == ' ')
    {
        strcpy(&s[strlen(s) - 1], &s[strlen(s)]);
    }
    for (i = 0; i < strlen(s) - 1; i++)
    {
        if (s[i] == ' ')
        {
            s[i + 1] = to_upper(s[i + 1]);
        }
        else
        {
            s[i + 1] = to_lower(s[i + 1]);
        }
    }
    s[strlen(s) - 1] = '\0'; 
}
char *upper(char s[])
{
    int i;
    for (i = 0; i < strlen(s); i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            s[i] -= 32;
        }
    }
    return s;
}

void addSv(sinhvien *sv)
{
    sinhvien Sv;
    int day, month, year;
    char ngayThangNam[20];
    printf("Moi ban nhap ho dem: ");
    fgets(Sv.middle, 30, stdin);
    standard(Sv.middle);
    printf("Moi ban nhap ten: ");
    fgets(Sv.name, 30, stdin);
    standard(Sv.name);
    printf("Moi ban nhap ngay thang nam sinh: ");
    do
    {
        fgets(ngayThangNam, sizeof(ngayThangNam), stdin);

        char *token = strtok(ngayThangNam, "/-.");

        day = atoi(token);
        token = strtok(NULL, "/-.");

        month = atoi(token);
        token = strtok(NULL, "/-.");

        year = atoi(token);
        if ((day > 31 && month == 1) || (day > 29 && month == 2) || (day > 31 && month == 3) || (day > 30 && month == 4) || (day > 31 && month == 5) || (day > 30 && month == 6) || (day > 31 && month == 7) || (day > 31 && month == 8) || (day > 30 && month == 9) || (day > 31 && month == 10) || (day > 30 && month == 11) || (day > 31 && month == 12) || (month > 12))
        {
            printf("Ngay sinh khong hop le! Moi ban nhap lai ");
        }
    } while ((day > 31 && month == 1) || (day > 29 && month == 2) || (day > 31 && month == 3) || (day > 30 && month == 4) || (day > 31 && month == 5) || (day > 30 && month == 6) || (day > 31 && month == 7) || (day > 31 && month == 8) || (day > 30 && month == 9) || (day > 31 && month == 10) || (day > 30 && month == 11) || (day > 31 && month == 12) || (month > 12));

    printf("Ban da nhap ngay sinh: %d/%d/%d\n", day, month, year);
    // getchar();
    Sv.birth.ngay = day;
    Sv.birth.thang = month;
    Sv.birth.nam = year;
    printf("Moi ban nhap vao gioi tinh cua minh: ");
    fgets(Sv.sex, 10, stdin);
    standard(Sv.sex);
    printf("Moi ban nhap vao dia chi: \n");
    printf("-So nha: ");
    fgets(Sv.OfSv.home, 5, stdin);
    standard(Sv.OfSv.home);
    printf("-Ten duong: ");
    fgets(Sv.OfSv.street, 30, stdin);
    standard(Sv.OfSv.street);
    printf("-Thanh pho: ");
    fgets(Sv.OfSv.city, 30, stdin);
    *sv = Sv;
}
// ham sap xep sinh vien theo ten
void swap(sinhvien *sv1, sinhvien *sv2)
{
    sinhvien tmp = *sv1;
    *sv1 = *sv2;
    *sv2 = tmp;
}
void sortSv(sinhvien list[], int l, int r)
{
    int i = l, j = r;
    char pivot_name[30], pivot_middle[30];
    strcpy(pivot_name, list[(l + r) / 2].name);
    strcpy(pivot_name, upper(pivot_name));
    strcpy(pivot_middle, list[(l + r) / 2].middle);
    strcpy(pivot_middle, upper(pivot_middle));
    do
    {
        char sv1[30];
        strcpy(sv1, list[i].name);
        char sv2[30];
        strcpy(sv2, list[j].name);
        while (strcmp(pivot_name, upper(sv1)) > 0)
        {
            i++;
            strcpy(sv1, list[i].name);
        }
        while (strcmp(pivot_name, upper(sv2)) < 0)
        {
            j--;
            strcpy(sv2, list[j].name);
        }
        if (strcmp(pivot_name, upper(sv2)) == 0)
        {
            char mSv1[30];
            strcpy(mSv1, list[i].name);
            char mSv2[30];
            strcpy(mSv2, list[j].name);
            if (strcmp(pivot_middle, upper(mSv1)) > 0)
                i++;
            if (strcmp(pivot_middle, upper(mSv2)) < 0)
                j--;
        }
        if (i <= j)
        {
            swap(&list[i], &list[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (j > l)
        sortSv(list, l, j);
    if (i < r)
        sortSv(list, i, r);
}
// ham xoa sinh vien
void deleteMsv(sinhvien list[], idmail ID[], int *n, int sv)
{
    int i;
    for (i = sv; i < (*n); i++)
    {
        list[i] = list[i + 1];
        ID[i] = ID[i + 1];
    }
    (*n)--;
}
void deleteAll(char fileName[])
{
    FILE *sv;
    sv = fopen(fileName, "wb+");
    if (sv == NULL)
    {
        printf("File khong ton tai!\n");
        return;
    }
    char n = '\0';
    fwrite(&n, sizeof(n), 1, sv);
    sumSv = 0;
}
// tim sinh vien theo ten
int binarySearchName(sinhvien list[], idmail ID[], int left, int right, char Name[])
{
    int p;
    while (left <= right)
    {
        p = left + (right - left) / 2;
        char tmp[100];
        strcpy(tmp, list[p].name);
        if (strcmp(upper(tmp), upper(Name)) == 0)
        {
            return p;
        }
        else if (strcmp(upper(tmp), upper(Name)) < 0)
        {
            left = p + 1;
        }
        else
        {
            right = p - 1;
        }
    }
    return -1;
}
// tim sinh vien theo msv
int binarySearchMsv(idmail ID[], int left, int right, long long idsv)
{
    int p;
    while (left <= right)
    {
        p = left + (right - left) / 2;
        if (ID[p].id == idsv)
        {
            return p;
        }
        else if (ID[p].id > idsv)
        {
            right = p - 1;
        }
        else
        {
            left = p + 1;
        }
    }
    return -1;
}
int inputMsv()
{
    long long id;
    int tmp = -2;
    int count = 5;
    scanf("%lld", &id);
    getchar();
    delSv = id;
    tmp = binarySearchMsv(ID, 0, sumSv, id);
    while (tmp == -1 && count != 0)
    {
        printf("Khong tim thay sinh vien ban muon!!!\n");
        printf("Moi ban nhap lai: ");
        scanf("%lld", &id);
        getchar();
        if (id == 0)
            break;
        delSv = id;
        tmp = binarySearchMsv(ID, 0, sumSv, id);
        count--;
    }
    return tmp;
}
// ham cap ma sinh vien va email
void initId()
{
    // tach chuoi thanh 3 phan
    char chuoi1[3]; // lay nien khoa cua nam hoc sinh vien
    int i;
    for (i = 0; i < 2; i++)
    {
        chuoi1[i] = fileName[i];
    } // nien khoa lay 2 ky tu dau cua chuoi me
    chuoi1[i] = '\0';
    int j = 0;
    char chuoi2[10];
    for (i = 2; i < strlen(fileName); i++)
    {
        if (!isdigit(fileName[i]))
        {
            chuoi2[j++] = fileName[i];
        }
    }
    chuoi2[j] = '\0';
    char chuoi3[2];
    chuoi3[0] = fileName[strlen(fileName) - 1];
    chuoi3[1] = '\0';
    // chuoi 2 la cac ky tu the hien nganh dang hoc
    char phu[] = ".txt";
    char chuoiphu[10];
    strcpy(chuoiphu, chuoi2);
    strcat(chuoiphu, phu);
    int k = 0;
    while (k < strlen(chuoiphu))
    {
        k++;
    }
    chuoiphu[k] = '\0';
    char manganh[3];
    FILE *f;
    f = fopen(chuoiphu, "r");
    if (f == NULL)
    {
        printf("Khong tim thay file\n");
        exit(1);
    }
    else
    {
        int n;
        fscanf(f, "%d", &n);
        sprintf(manganh, "%d", n);
        fclose(f);
    }
    // chuyen n nay thanh chuoi va noi vao chuoi chinh
    char s[10];
    char c[] = "001";
    strcat(s, manganh);
    strcat(s, chuoi1); // noi nien khoa vao chuoi
    strcat(s, chuoi3);
    strcat(s, c);
    long long num = atoll(s);
    for (i = 0; i < sumSv; i++)
    {
        ID[i].id = num + i;
    }
}
void initEmail()
{
    int i;
    char aim[100];
    for (i = 0; i < sumSv; i++)
    {
        sprintf(aim, "%lld", ID[i].id);
        strcpy(ID[i].email, strcat(aim, "@sv1.dut.udn.vn"));
    }
}
// ham dinh dang bang sinh vien
void format()
{

    int i;
    for (i = 0; i < 169; i++)
    {
        if (i == 0 || i == 168 || i == 120 || i == 104 || i == 72 || i == 48 || i == 16)
            printf("+");
        else
            printf("-");
    }
    printf("\n");
}
void formatHead()
{
    format();
    printf("|%8s\t|%20s\t\t|%16s\t|%19s\t\t|%10s     |%26s%22s\n", "ID", "Ho va Ten", "Ngay Sinh", "Email", "Gioi tinh", "Dia chi", "|");
    format();
}
// in danh sach sinh vien
void printSv(sinhvien sv, idmail msv)
{
    char name[30], middle[30], fullName[60];
    strcpy(name, sv.name);
    strcpy(middle, sv.middle);
    strcpy(fullName, middle);
    strcat(fullName, " ");
    strcat(fullName, name);
    printf("\n|%11lld\t|%26s\t%s%8d-%2d-%2d\t|%27s\t|%4s           |%6s-%s-%s", msv.id, fullName, "|", sv.birth.ngay, sv.birth.thang, sv.birth.nam, msv.email, sv.sex, sv.OfSv.home, sv.OfSv.street, sv.OfSv.city);
    printf("|%16s %31s %23s %31s %15s%47s|", "|", "|", "|", "|", "|", " ");
}
void scanlist()
{
    int i;
    for (i = 0; i < sumSv; i++)
    {
        printSv(list[i], ID[i]);
    }
    printf("\n");
    format();
}
void nameFile(char fileName[])
{
    do
    {
        fgets(fileName, 100, stdin);
        fileName[strlen(fileName) - 1] = '\0';
        if (test(fileName) == 0)
        {
            printf("Lop nhap vao khong hop le!Moi ban nhap lai: ");
        }
    } while (test(fileName) == 0);
}
void readFromFile()
{
    FILE *sv;
    sv = fopen(fileName, "ab+");
    if (sv == NULL)
    {
        printf("file khong ton tai!\n");
        return;
    }
    fread(&sumSv, sizeof(int), 1, sv);
    fread(&check, sizeof(int), 1, sv);
    int i;
    for (i = 0; i < sumSv; i++)
    {
        fread(&ID[i], sizeof(ID), 1, sv);
        fread(&list[i], sizeof(sinhvien), 1, sv);
    }
    fclose(sv);
}
void writeToFile()
{
    FILE *sv;
    sv = fopen(fileName, "wb+");
    if (sv == NULL)
    {
        printf("file khong ton tai!\n");
        return;
    }
    fwrite(&sumSv, sizeof(int), 1, sv);
    fwrite(&check, sizeof(int), 1, sv);
    int i;
    for (i = 0; i < sumSv; i++)
    {
        fwrite(&ID[i], sizeof(ID), 1, sv);
        fwrite(&list[i], sizeof(sinhvien), 1, sv);
    }
    fclose(sv);
}
int choice()
{
    printf("\n========================================\n");
    printf("    1.Lop vua chon o tren.\n");
    printf("    2.chon lop khac.\n");
    printf("    3.Dung\n");
    printf("========================================\n");
    int option = 0;
    printf("Nhap lua chon: ");
    scanf("%d", &option);
    getchar();
    while (option != 1 && option != 2 && option != 3)
    {
        printf("Moi nhap lai lua chon cua ban!\n");
        printf("Nhap lua chon: ");
        scanf("%d", &option);
        getchar();
    }
    return option;
}
void searchNameSv()
{
    char Name[30];
    printf("Moi ban nhap ten can tim kiem: ");
    fgets(Name, 30, stdin);
    Name[strlen(Name) - 1] = '\0';
    int i;
    int location = binarySearchName(list, ID, 0, sumSv - 1, Name);
    if (location != -1)
    {
        formatHead();
        char tmp[30];
        for (i = 0; i < sumSv; i++)
        {
            strcpy(tmp, list[i].name);
            if (strcmp(upper(tmp), upper(Name)) == 0)
            {
                printSv(list[i], ID[i]);
            }
        }
        printf("\n");
        format();
    }
    while (location == -1)
    {
        // char Name[30];
        printf("Khong tim thay sinh vien trong danh sach!\n");
        printf("Ban co muon tiep tuc tim kiem hay khong?\n");
        printf("1.Yes\n");
        printf("2.No\n");
        int choice;
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        getchar();
        if (choice == 1)
        {
            printf("Moi ban nhap ten can tim kiem: ");
            fgets(Name, 30, stdin);
            Name[strlen(Name) - 1] = '\0';
            int i;
            int location = binarySearchName(list, ID, 0, sumSv - 1, Name);
            if (location != -1)
            {
                formatHead();
                char tmp[30];
                for (i = 0; i < sumSv; i++)
                {
                    strcpy(tmp, list[i].name);
                    if (strcmp(upper(tmp), upper(Name)) == 0)
                    {
                        printSv(list[i], ID[i]);
                    }
                }
                printf("\n");
                format();
            }
        }
        else if (choice == 2)
        {
            break;
        }
    }
}
void select1()
{
    sumSv = 0;
    printf("Nhap ten lop can them sinh vien:");
    nameFile(fileName); 
    readFromFile();    
    res = sumSv;
    printf("\nTrong danh sach co %d sinh vien!", res);
    printf("So sinh vien can them la: ");
    scanf("%d", &count);
    getchar();
    sumSv += count;
    int i;
    for (i = res; i < sumSv; i++)
    {
        printf("Nhap thong tin cua sinh vien thu %d\n", i + 1);
        addSv(&list[i]);
    }
    printf("So sinh vien trong danh sach hien tai la: %d\n", sumSv);
    check = 0;
    writeToFile();
}
void select2()
{
    printf("Nhap ten lop ban muon sap xep: ");
    nameFile(fileName);
    readFromFile();
    sortSv(list, 0, sumSv - 1);
    printf("Sap xep thanh cong!");
    initId();
    printf("\nCap ma sinh vien thanh cong!");
    initEmail();
    printf("\nCap email cho sinh vien thanh cong!");
    check = 2;
    writeToFile();
    printf("\n");
    formatHead();
    scanlist();
}
void note()
{
    if (fileName[0] != '\0')
    {
        int option7_1 = choice();
        if (option7_1 == 0)
            return;
        switch (option7_1)
        {
        case 1:
            readFromFile();
            break;
        case 2:
            printf("Nhap ten lop can xuat danh sach sinh vien: ");
            nameFile(fileName);
            sumSv = 0;
            readFromFile();
            break;
        }
    }
    else if (fileName[0] == '\0')
    {
        printf("Nhap ten lop can xuat danh sach sinh vien: ");
        nameFile(fileName);
        sumSv = 0;
        readFromFile();
    }
    if (sumSv == 0)
    {
        printf("Danh sach sinh vien rong!!!\n");
        printf("Hay them sinh vien vao danh sach!!!\n");
    }
    else
    {
        formatHead();
        scanlist();
    }
}
void select3()
{
    printf("\n========================================\n");
    printf("    1.Xoa theo ma sinh vien.\n");
    printf("    2.Xoa tat ca.\n");
    printf("    3.Dung\n");
    printf("========================================\n");
    printf("Nhap lua chon: ");
    int option;
    scanf("%d", &option);
    getchar();
    int limit = 4;
    while (option != 1 && option != 2 && option != 3)
    {
        printf("Moi ban nhap lai lua chon!\n");
        printf("Nhap lua chon: ");
        --limit;
        scanf("%d", &option);
        getchar();
    }
    switch (option)
    {
    case 1:
        /* code */
        if (fileName[0] != '\0')
        {
            int option_1 = choice();
            if (option_1 == 3)
                break;
            switch (option_1)
            {
            case 1:
                readFromFile();
                break;
            case 2:
                printf("Nhap ten lop can xuat: ");
                nameFile(fileName);
                readFromFile();
                break;
            }
        }
        else if ('\0' == fileName[0])
        {
            printf("Nhap ten lop can xuat danh sach sinh vien: ");
            nameFile(fileName);
            readFromFile();
        }
        formatHead();
        scanlist();
        printf("\n");
        printf("Nhap msv can xoa: ");
        sv = inputMsv(); // sv la index cua sinh vien can xoa trong danh sach lop
        if (sv == -1)
        {
            printf("Da dung xoa!\n");
            formatHead();
            scanlist();
            break;
        }
        deleteMsv(list, ID, &sumSv, sv);
        writeToFile();
        printf("Da xoa sinh vien co id: %lld\n", delSv);
        writeToFile();
        formatHead();
        scanlist();
        break;
    case 2:
        printf("Ban co chac muon xoa het toan bo sinh vien trong danh sach khong (y/n): ");
        fgets(confirmDelAll, 2, stdin);
        if (strcmp(confirmDelAll, "Y") == 0 || strcmp(confirmDelAll, "y") == 0)
        {
            if (fileName[0] != '\0')
            {
                int option2 = choice();
                if (option2 == 0)
                    break;
                switch (option2)
                {
                case 1:
                    deleteAll(fileName);

                    break;
                case 2:
                    printf("Nhap ten lop can xoa: ");
                    nameFile(fileName);
                    deleteAll(fileName);
                    break;
                case 0:
                    break;
                }
            }
            else if (fileName[0] == 0)
            {
                printf("Nhap lai ten cua lop can xoa: ");
                nameFile(fileName);
                deleteAll(fileName);
            }
        }
        else
            ;
        break;
    case 3:
        break;
    }
}
void select4()
{
    printf("========================================\n");
    printf("    1.Tim theo ma sinh vien.\n");
    printf("    2.Tim theo ten sinh vien.\n");
    printf("    3.Dung\n");
    printf("========================================\n");
    printf("Nhap lua chon: ");
    int option;
    scanf("%d", &option);
    getchar();
    while (option != 1 && option != 2 && option != 3)
    {
        printf("Moi ban nhap lai lua chon!\n");
        printf("Nhap lua chon: ");
        scanf("%d", &option);
        getchar();
    }
    switch (option)
    {
    case 1:
        if (fileName[0] != '\0')
        {
            int option_1 = choice();
            if (option_1 == 0)
                break;
            switch (option_1)
            {
            case 1:
                break;
            case 2:
                printf("Nhap ten lop can xuat: ");
                nameFile(fileName);
                readFromFile();
                break;
            }
        }
        else if ('\0' == fileName[0])
        {
            printf("Nhap ten lop can xuat danh sach sinh vien: ");
            nameFile(fileName);
        }
        readFromFile();
        printf("Nhap ma sinh vien can xuat: ");
        idSv = inputMsv();
        formatHead();
        printSv(list[idSv], ID[idSv]);
        printf("\n");
        format();
        break;
    case 2:
        if (fileName[0] != '\0')
        {
            int option2 = choice();
            if (option2 == 0)
                break;
            switch (option2)
            {
            case 1:
                break;
            case 2:
                printf("Nhap ten lop can tim danh sach sinh vien: ");
                nameFile(fileName);
                break;
            case 0:
                break;
            }
        }
        else if (fileName[0] == '\0')
        {
            printf("Moi ban nhap lai lop can tim: ");
            nameFile(fileName);
        }
        readFromFile();
        searchNameSv();
        break;
    case 3:
        break;
    }
}
void select5()
{
    if (check)
    {
        readFromFile();
        initId();
        writeToFile();
        printf("Cap ma sinh vien thanh cong!!!\n");
    }
    else
        printf("LOI CHUA SAP XEP!!!\n");
}
void select6()
{
    if (check)
    {
        readFromFile();
        initEmail();
        writeToFile();
        printf("Cap email thanh cong!!!\n");
    }
    else
        printf("LOI CHUA SAP XEP!!!\n");
}
void select7()
{
    if (fileName[0] != '\0')
    {
        int option7_1 = choice();
        if (option7_1 == 3)
            return;
        switch (option7_1)
        {
        case 1:
            readFromFile();
            break;
        case 2:
            printf("Nhap ten lop can xuat danh sach sinh vien: ");
            nameFile(fileName);
            sumSv = 0;
            readFromFile();
            break;
        }
    }
    else if (fileName[0] == '\0')
    {
        printf("Nhap ten lop can xuat danh sach sinh vien: ");
        nameFile(fileName);
        sumSv = 0;
        readFromFile();
    }
    if (sumSv == 0)
    {
        printf("Danh sach sinh vien rong!!!\n");
        printf("Hay them sinh vien vao danh sach!!!\n");
    }
    else
    {
        formatHead();
        scanlist();
    }
}
void Intro()
{
    printf("\t\t\t\t ______________________________________________________________________________________________\n");
    printf("\t\t\t\t|                                                                                              |\n");
    printf("\t\t\t\t|                                 DO AN PBL1: LAP TRINH TINH TOAN                              |\n");
    printf("\t\t\t\t|                                                                                              |\n");
    printf("\t\t\t\t|                       DE TAI: XAY DUNG UNG DUNG QUAN LY DANH SACH SINH VIEN                  |\n");
    printf("\t\t\t\t|                                                                                              |\n");
    printf("\t\t\t\t|                                                                                              |\n");
    printf("\t\t\t\t|                                        Giao vien huong dan: Nguyen Thi Minh Hy               |\n");
    printf("\t\t\t\t|                                                                                              |\n");
    printf("\t\t\t\t|                                                                                              |\n");
    printf("\t\t\t\t|         Sinh vien thuc hien:                                                                 |\n");
    printf("\t\t\t\t|                            Nguyen Huu Nhat Huy(23T_DT1)   - MSV: 102230191                   |\n");
    printf("\t\t\t\t|                            Dang Ngoc Huy(23T_DT1)         - MSV: 102230190                   |\n");
    printf("\t\t\t\t|                                                                                              |\n");
    printf("\t\t\t\t|______________________________________________________________________________________________|\n");
}
void menu()
{
    do
    {
        printf("1.Them sinh vien \n");
        printf("2.Sap xep sinh vien \n");
        printf("3.Xoa sinh vien \n");
        printf("4.Tim sinh vien \n");
        printf("5.Cap ma sinh vien \n");
        printf("6.Cap email \n");
        printf("7.In ra danh sach sinh vien \n");
        printf("8.Thoat chuong trinh \n");
        printf("Moi nhap vao lua chon cua ban: ");
        scanf("%d", &chooseMenu);
        getchar();
        if (chooseMenu == 2)
            check = 2;
        switch (chooseMenu)
        {
        case 1:
            select1();
            break;
        case 2:
            select2();
            break;
        case 3:
            select3();
            break;
        case 4:
            select4();
            break;
        case 5:
            select5();
            break;
        case 6:
            select6();
            break;
        case 7:
            select7();
            break;
        case 8:
            break;
        default:
            printf("Nhap lai lua chon cua ban!!!\n");
        }
    } while (chooseMenu != 8);
}