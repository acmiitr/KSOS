#include <stdint.h>
#include <stdbool.h>
#include "FAT12.h"
#include "hardware.h"
#include "dadio.h"
#include"string.h"

#define bpbBytesPerSector 512
#define bpbSectorsPerCluster 1
#define bpbReservedSectors 1
#define bpbNumberOfFATs 2
#define bpbRootEntries 512
#define bpbTotalSectors 2880
#define bpbMedia 0xf0
#define bpbSectorsPerFAT 6
#define Max_Name_Length 11

 static bool string_compare(char* str1, char* str2);
 uint16_t get_next_cluster(uint16_t cluster_number,uint8_t* pointer_to_fat);

static uint8_t data_sect_no;
static uint32_t data_sect_address;
static uint8_t root_sect_no;
static uint32_t root_sect_address;
static uint8_t fat_sect_no;
static uint32_t fat_sect_address;

typedef struct __attribute__((__packed__)) file_Meta
{
    uint32_t file_size;
    uint16_t starting_data_cluster_number;
} file_Meta;

static file_Meta file;
//uint32_t buffer_read_[];
//extern uint8_t root_read_[];
//uint32_t fat_buffer_read[];

void initialize_FAT(uint32_t data_sect, uint32_t root_sect, uint32_t fat_sect)
{
    data_sect_no = data_sect;
    data_sect_address = data_sect * bpbBytesPerSector;
    root_sect_no = root_sect;
    root_sect_address = root_sect * bpbBytesPerSector;
    fat_sect_no = fat_sect;
    fat_sect_address = fat_sect * bpbBytesPerSector;
}

bool FAT_find_file(char *filename)
{
    uint8_t root_read_[512 * data_sect_no - root_sect_no];
    read_sectors_ATA_PIO((uint32_t)root_read_, root_sect_no, data_sect_no - root_sect_no);
    uint8_t *pointer = (uint8_t *)root_read_;
    char root_name[13] ;
    for (int i = 0; i < bpbRootEntries; i++)
    {
        int j;
        //Get the file name with extension
        //--------------------------------------------
        for (j = 0; j < 8; j++)
            {
                if(pointer[j]==' ')
                break;
            root_name[j] = pointer[j];
            }
        root_name[j] = '.';
        root_name[j+1]=pointer[8];
        root_name[j+2]=pointer[9];
        root_name[j+3]=pointer[10];
        root_name[j+4]=0;
        //--------------------------------------------
        if (string_compare(root_name, filename))
        {
            file.starting_data_cluster_number = pointer[26] + (pointer[27] << 8);                           //Considering the little endian encoding
            file.file_size = pointer[28] + (pointer[29] << 8) + (pointer[30] << 24) + (pointer[31] << 16);  //Considering the little endian encoding
            return true;
        }
        pointer += 32;
    }
    file.starting_data_cluster_number = 0;
    file.file_size = 0;
    return false;
}

void read_file(char *filename)
{
    if(!FAT_find_file(filename))
        monitor_puts("File not found!");

    else //If  file found
    {   
        uint32_t data_cluster_address=data_sect_address+(file.starting_data_cluster_number-2)*512;
        
        uint16_t fat_buffer_read[256*(root_sect_no-fat_sect_no)];
        char buffer_read_[513];
        char file_read[file.file_size+1];

        read_sectors_ATA_PIO((uint32_t)fat_buffer_read,fat_sect_no,root_sect_no-fat_sect_no);
        
        uint16_t fat_value=file.starting_data_cluster_number;
        int count=0,t;
        do
        {
            data_cluster_address=data_sect_address+(fat_value-2)*512;
            fat_value=get_next_cluster(fat_value,(uint8_t*)fat_buffer_read);
            
            read_sectors_ATA_PIO((uint32_t)buffer_read_,data_cluster_address/512,1);            //reads the data from data cluster
            t=0;
            
            //-------------------------------------
            while(t<512 && count<file.file_size)
            {   
                file_read[count]=buffer_read_[t];
                count++;t++;
            }
            //----------------------------------------
        }
        while(fat_value!=0xfff);
        monitor_puts(file_read);//Display the read file
        
    }
}
uint16_t get_next_cluster(uint16_t cluster_number,uint8_t* pointer_to_fat)
{
    int offset=(cluster_number/2)*3;
    if(cluster_number&1)
    offset+=1;
    uint16_t next_cluster_number;
    if(cluster_number&1)
        next_cluster_number=(pointer_to_fat[offset+1]<<4)+((pointer_to_fat[offset]&0xF0)>>4);
    else
        next_cluster_number=pointer_to_fat[offset]+((pointer_to_fat[offset+1]&0x0F)<<8);

return next_cluster_number;
}

static bool string_compare(char *str1, char *str2)
{
    int i = 0;
    while (str1[i])
    {
        if (str1[i] != str2[i])
            return false;
        i++;
    }
    if (str2[i])
        return false;
    return true;
}
