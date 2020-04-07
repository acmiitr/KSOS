#include <stdint.h>
#include <stdbool.h>
#include"FAT12.h"
#include"hardware.h"
#include"dadio.h"

#define bpbBytesPerSector 512
#define bpbSectorsPerCluster  1
#define bpbReservedSectors 1
#define bpbNumberOfFATs	 2
#define bpbRootEntries 	 512
#define bpbTotalSectors  2880
#define bpbMedia  0xf0  
#define bpbSectorsPerFAT  6     ;We need all this
#define Max_Name_Length 11

static bool string_compare(char* str1, char* str2);

static uint8_t data_sect_no;
static uint32_t data_sect_address;
static uint8_t root_sect_no;
static uint32_t root_sect_address;
static uint8_t fat_sect_no;
static uint32_t fat_sect_address;

static int file_size;
static int starting_data_cluster_number;

uint32_t buffer_read_; 
uint32_t fat_buffer_read;
char* file_read;

void initialize_FAT(uint32_t data_sect,uint32_t root_sect, uint32_t fat_sect)
{
    data_sect_no=data_sect;
    data_sect_address=data_sect* bpbBytesPerSector;
    root_sect_no=root_sect;
    root_sect_address=root_sect* bpbBytesPerSector;
    fat_sect_no=fat_sect;
    fat_sect_address=fat_sect* bpbBytesPerSector;
}

bool FAT_find_file(char* filename)
{

    read_sectors_ATA_PIO(buffer_read_,root_sect_address,data_sect_no-root_sect_no);
    uint8_t* pointer=(uint8_t*)buffer_read_;
    char* root_name[12];
    for(int i=0;i<bpbRootEntries;i++)
    {
        //Get the file name with extension
        //--------------------------------------------
        for(int j=0;i<8;i++)
            root_name[j]=pointer[j];
        root_name[8]='.';
        for(int j=8;i<11;i++)
            root_name[j+1]=pointer[j];
        //--------------------------------------------
        if(string_compare(root_name,filename))
            {
               starting_data_cluster_number=pointer[26]+pointer[27]>>8;//Considering the little endian encoding
                file_size=pointer[28]+(pointer[29]>>8)+(pointer[30]>>16)+(pointer[31]>>24);//Considering the little endian encoding
                return true;
            }
        pointer+=32;  
    }
    starting_data_cluster_number=0;
    file_size=0;
    return false;
}


void read_file(char* filename)
{
    if(!FAT_find_file(filename))
        monitor_puts("File not found!");

    else//file found
    {
        uint32_t starting_data_cluster_address=fat_sect_address+(starting_data_cluster_number-2)*512;
        uint32_t fat_sector_address= fat_sect_address+ (starting_data_cluster_number/256)*512;
        
        char* file_read[file_size];

        read_sectors_ATA_PIO(buffer_read_,starting_data_cluster_address,1);
        read_sectors_ATA_PIO(fat_buffer_read,fat_sector_address,1);

        if(file_size<512)
            {
                uint8_t * pointer=(uint8_t*)buffer_read_;
                for(int i=0;i<file_size;i++)
                    file_read[i]=(char)pointer[i];
            }
    }
}



static bool string_compare(char* str1, char* str2)
{
	int i = 0;
	while (str1[i])
	{
		if(str1[i] != str2[i]) return false;
		i++;
	}
	if(str2[i]) return false;
	return true;
}

