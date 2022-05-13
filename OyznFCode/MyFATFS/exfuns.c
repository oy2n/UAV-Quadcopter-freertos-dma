/*
 * exfuns.c
 *
 *  Created on: Mar 20, 2022
 *      Author: Oyzn
 */
#include "../MyFATFS/exfuns.h"
#include "../MyFATFS/fatfs_sd.h"

#include "main.h"
#include "cmsis_os.h"
#include "fatfs.h"
#include <string.h>
#include <stdarg.h>

extern USART_HandleTypeDef husart1;
FATFS fs;
FATFS *pfs;
FIL fil;

void UART_Printf(const char* fmt, ...) {
    char buff[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buff, sizeof(buff), fmt, args);
    HAL_USART_Transmit(&husart1, (uint8_t*)buff, strlen(buff), HAL_MAX_DELAY);
    va_end(args);
}

void TestFatfs2()
{
	UINT bw;
	uint8_t text[] = "123123123123\r\n";
	if(f_mount(&USERFatFS,(const TCHAR*)USERPath,0) != FR_OK)
	{
		UART_Printf("f_mount() failed, res = %d\r\n", retUSER);
	}
	else
	{
		if(f_open(&USERFile,"test.txt",FA_OPEN_APPEND | FA_WRITE | FA_OPEN_ALWAYS) != FR_OK)
		{
			 UART_Printf("f_open() failed, res = %d\r\n", retUSER);
		}
		else
		{
			if(f_write(&USERFile, text, sizeof(text), &bw) != FR_OK)
			{
				UART_Printf("f_write() failed, res = %d\r\n", retUSER);
			}
			else
			{
				f_close(&USERFile);
				UART_Printf("ok\r\n");
			}
		}
	}
}
void TestFatfs() {
    FATFS fs;
    FRESULT res;
    UART_Printf("Ready!\r\n");

    // mount the default drive
    res = f_mount(&fs, "", 0);
    if(res != FR_OK) {
        UART_Printf("f_mount() failed, res = %d\r\n", res);
        return;
    }

    UART_Printf("f_mount() done!\r\n");

    uint32_t freeClust;
    FATFS* fs_ptr = &fs;
    res = f_getfree("", &freeClust, &fs_ptr); // Warning! This fills fs.n_fatent and fs.csize!
    if(res != FR_OK) {
        UART_Printf("f_getfree() failed, res = %d\r\n", res);
        return;
    }

    UART_Printf("f_getfree() done!\r\n");

    uint32_t totalBlocks = (fs.n_fatent - 2) * fs.csize;
    uint32_t freeBlocks = freeClust * fs.csize;

    UART_Printf("Total blocks: %lu (%lu Mb)\r\n", totalBlocks, totalBlocks / 2000);
    UART_Printf("Free blocks: %lu (%lu Mb)\r\n", freeBlocks, freeBlocks / 2000);

    DIR dir;
    res = f_opendir(&dir, "/");
    if(res != FR_OK) {
        UART_Printf("f_opendir() failed, res = %d\r\n", res);
        return;
    }

    FILINFO fileInfo;
    uint32_t totalFiles = 0;
    uint32_t totalDirs = 0;
    UART_Printf("--------\r\nRoot directory:\r\n");
    for(;;) {
        res = f_readdir(&dir, &fileInfo);
        if((res != FR_OK) || (fileInfo.fname[0] == '\0')) {
            break;
        }

        if(fileInfo.fattrib & AM_DIR) {
            UART_Printf("  DIR  %s\r\n", fileInfo.fname);
            totalDirs++;
        } else {
            UART_Printf("  FILE %s\r\n", fileInfo.fname);
            totalFiles++;
        }
    }

    UART_Printf("(total: %lu dirs, %lu files)\r\n--------\r\n", totalDirs, totalFiles);

    res = f_closedir(&dir);
    if(res != FR_OK) {
        UART_Printf("f_closedir() failed, res = %d\r\n", res);
        return;
    }

    UART_Printf("Writing to log.txt...\r\n");

    char writeBuff[128];
    snprintf(writeBuff, sizeof(writeBuff), "Total blocks: %lu (%lu Mb); Free blocks: %lu (%lu Mb)\r\n",
        totalBlocks, totalBlocks / 2000,
        freeBlocks, freeBlocks / 2000);

    FIL logFile;
    res = f_open(&logFile, "log.txt", FA_OPEN_APPEND | FA_WRITE);
    if(res != FR_OK) {
        UART_Printf("f_open() failed, res = %d\r\n", res);
        return;
    }

    unsigned int bytesToWrite = strlen(writeBuff);
    unsigned int bytesWritten;
    res = f_write(&logFile, writeBuff, bytesToWrite, &bytesWritten);
    if(res != FR_OK) {
        UART_Printf("f_write() failed, res = %d\r\n", res);
        return;
    }

    if(bytesWritten < bytesToWrite) {
        UART_Printf("WARNING! Disk is full, bytesToWrite = %lu, bytesWritten = %lu\r\n", bytesToWrite, bytesWritten);
    }

    res = f_close(&logFile);
    if(res != FR_OK) {
        UART_Printf("f_close() failed, res = %d\r\n", res);
        return;
    }

    UART_Printf("Reading file...\r\n");
    FIL msgFile;
    res = f_open(&msgFile, "log.txt", FA_READ);
    if(res != FR_OK) {
        UART_Printf("f_open() failed, res = %d\r\n", res);
        return;
    }

    char readBuff[128];
    unsigned int bytesRead;
    res = f_read(&msgFile, readBuff, sizeof(readBuff)-1, &bytesRead);
    if(res != FR_OK) {
        UART_Printf("f_read() failed, res = %d\r\n", res);
        return;
    }

    readBuff[bytesRead] = '\0';
    UART_Printf("```\r\n%s\r\n```\r\n", readBuff);

    res = f_close(&msgFile);
    if(res != FR_OK) {
        UART_Printf("f_close() failed, res = %d\r\n", res);
        return;
    }

    // Unmount
    res = f_mount(NULL, "", 0);
    if(res != FR_OK) {
        UART_Printf("Unmount failed, res = %d\r\n", res);
        return;
    }

    UART_Printf("Done!\r\n");
}
