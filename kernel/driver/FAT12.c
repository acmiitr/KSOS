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
#define bpbSectorsPerFAT  6 
#define Max_Name_Length 11

static bool string_compare(char* str1, char* str2);

static uint8_t data_sect_no;
static uint32_t data_sect_address;
static uint8_t root_sect_no;
static uint32_t root_sect_address;
static uint8_t fat_sect_no;
static uint32_t fat_sect_address;

typedef struct __attribute__ ((__packed__)) file_Meta {
	uint32_t file_size;
    uint16_t starting_data_cluster_number;
}file_Meta;



static file_Meta file ;
uint32_t buffer_read_[]; 
uint32_t fat_buffer_read[];

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
               file.starting_data_cluster_number=pointer[26]+pointer[27]<<8;//Considering the little endian encoding
                file.file_size=pointer[28]+(pointer[29]<<8)+(pointer[30]<<24)+(pointer[31]<<16);//Considering the little endian encoding
                return true;
            }
        pointer+=32;  
    }
    file.starting_data_cluster_number=0;
    file.file_size=0;
    return false;
}


void read_file(char* filename)
{
    if(!FAT_find_file(filename))
        monitor_puts("File not found!");

    else                     //If  file found
    {
        uint32_t data_cluster_address=data_sect_address+(file.starting_data_cluster_number-2)*512;
        uint32_t fat_sector_address= fat_sect_address;
        
        char* file_read[file.file_size];

        //read_sectors_ATA_PIO(buffer_read_,data_cluster_address,1);
        read_sectors_ATA_PIO(fat_buffer_read,fat_sector_address,root_sect_no-fat_sect_no);
        
        uint16_t* pointer_to_fat=(uint16_t*)fat_buffer_read;
        pointer_to_fat+= file.starting_data_cluster_number;
        int count=0;
        do
        {
            read_sectors_ATA_PIO(buffer_read_,data_cluster_address,1);
            char* reading=(char*)buffer_read_;
            int t=0;
            while(t<512 && count<file.file_size)
            {   
                file_read[count]=*reading;
                count++;t++;reading++;
            }
            //Defining the next cluster number from FAT and next adress in the data sector
            uint8_t next_cluster_number=(*pointer_to_fat)>>8;
            data_cluster_address=data_sect_address+(next_cluster_number-2)*512;         //next_cluster_number-2  as first and second not there
            
            
            if(*pointer_to_fat!=0xFFF8)                                               //update only if it is not the last 
            {
                pointer_to_fat=(uint16_t*)fat_buffer_read;
                pointer_to_fat+=next_cluster_number;
            }
        }
        while(*pointer_to_fat!=0xFFF8);

        // if(file.file_size<512)
        //     {
        //         uint8_t * pointer=(uint8_t*)buffer_read_;
        //         for(int i=0;i<file.file_size;i++)
        //             file_read[i]=(char)pointer[i];
        //     }
        //     else
        //     {
        //         uint16_t *pointer=(uint16_t*)fat_buffer_read;
        //         pointer+=file.starting_data_cluster_number%256;
        //         uint8_t next_cluster_number=(*pointer)>>8;

        //         while(*pointer!=0xFFF8)
        //         {
                    
        //         }
        //     }
            
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

